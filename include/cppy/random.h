#pragma once

#include <algorithm>
#include <chrono>
#include <random>
#include <vector>

#include "cppy/exception.h"
#include "cppy/internal/declare.h"

struct CPPY_Random
{
    std::mt19937 engine; // Mersenne Twister 19937 generator
};

/* Initialize an instance.
 */
CPPY_API CPPY_ERROR_t CPPY_RANDOM_init(CPPY_Random* const random);

/* Initialize an instance.
 *
 * Optional argument x controls seeding, as for Random.seed().
 */
CPPY_API CPPY_ERROR_t CPPY_RANDOM_init(CPPY_Random* const random, unsigned int x);

/* Initialize internal state from a seed.
 */
CPPY_API CPPY_ERROR_t CPPY_RANDOM_seed(CPPY_Random* const random, unsigned int a);

/* Return random integer in range [a, b], including both end points.
 */
template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
CPPY_ERROR_t CPPY_RANDOM_randint(CPPY_Random* const random, T a, T b, T* const result)
{
    if (a > b)
        return CPPY_ERROR_t::ValueError;
    std::uniform_int_distribution<T> dist(a, b);
    *result = dist(random->engine);
    return CPPY_ERROR_t::Ok;
}

/* x in the interval [0, 1).
 */
template <typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
CPPY_ERROR_t CPPY_RANDOM_random(CPPY_Random* const random, T* const result)
{
    std::uniform_real_distribution<T> dist(0.0, 1.0);
    *result = dist(random->engine);
    return CPPY_ERROR_t::Ok;
}

/* Get a random number in the range [a, b) or [a, b] depending on rounding.
 */
template <typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
CPPY_ERROR_t CPPY_RANDOM_uniform(CPPY_Random* const random, T a, T b, T* const result)
{
    if (a > b)
        return CPPY_ERROR_t::ValueError;
    std::uniform_real_distribution<T> dist(a, b);
    *result = dist(random->engine);
    return CPPY_ERROR_t::Ok;
}

/* Normal distribution.
 *
 * mu is the mean, and sigma is the standard deviation.
 */
template <typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
CPPY_ERROR_t CPPY_RANDOM_normalvariate(CPPY_Random* const random, T mu, T sigma, T* const result)
{
    std::normal_distribution<T> dist(mu, sigma);
    *result = dist(random->engine);
    return CPPY_ERROR_t::Ok;
}

/* Shuffle list x in place, and return None.
 */
template <class Iterable>
CPPY_ERROR_t CPPY_RANDOM_shuffle(CPPY_Random* const random, Iterable first, Iterable last)
{
    std::shuffle(first, last, random->engine);
    return CPPY_ERROR_t::Ok;
}

/* Choose a random element from a non-empty sequence.
 */
template <class Iterable>
CPPY_ERROR_t CPPY_RANDOM_choice(CPPY_Random* const random, Iterable first, Iterable last, typename std::iterator_traits<Iterable>::value_type* result)
{
    if (first == last)
        return CPPY_ERROR_t::IndexError;

    using iterator_category = typename std::iterator_traits<Iterable>::iterator_category;
    if constexpr (std::is_base_of_v<std::random_access_iterator_tag, iterator_category>)
    {
        const size_t length = std::distance(first, last);
        std::uniform_int_distribution<size_t> dist(0, length - 1);
        const size_t random_idx = dist(random->engine);
        *result = *(first + random_idx);
    }
    else
    {
        *result = *first;
        size_t count = 1;
        for (Iterable it = std::next(first); it != last; ++it, ++count)
        {
            std::uniform_int_distribution<size_t> dist(0, count);
            if (dist(random->engine) == 0)
            {
                *result = *it;
            }
        }
    }
    return CPPY_ERROR_t::Ok;
}
