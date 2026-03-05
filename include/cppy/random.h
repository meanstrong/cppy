#pragma once

#include <algorithm>
#include <chrono>
#include <random>
#include <vector>

#include "cppy/exception.h"
#include "cppy/internal/declare.h"

/* Random number generator base class used by bound module functions.
 */
class CPPY_API CPPY_RANDOM_Random
{
private:
    std::mt19937 engine; // Mersenne Twister 19937 generator

public:
    /* Initialize an instance.
     */
    CPPY_RANDOM_Random();

    /* Initialize an instance.
     *
     * Optional argument x controls seeding, as for Random.seed().
     */
    explicit CPPY_RANDOM_Random(unsigned int x);

    /* Initialize internal state from a seed.
     */
    void seed(unsigned int a);

    /* Return random integer in range [a, b], including both end points.
     */
    template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
    CPPY_ERROR_t randint(T a, T b, T* const result)
    {
        if (a > b)
            return CPPY_ERROR_t::ValueError;
        std::uniform_int_distribution<T> dist(a, b);
        *result = dist(engine);
        return CPPY_ERROR_t::Ok;
    }

    /* x in the interval [0, 1).
     */
    template <typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
    CPPY_ERROR_t random(T* const result)
    {
        std::uniform_real_distribution<T> dist(0.0, 1.0);
        *result = dist(engine);
        return CPPY_ERROR_t::Ok;
    }

    /* Get a random number in the range [a, b) or [a, b] depending on rounding.
     */
    template <typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
    CPPY_ERROR_t uniform(T a, T b, T* const result)
    {
        if (a > b)
            return CPPY_ERROR_t::ValueError;
        std::uniform_real_distribution<T> dist(a, b);
        *result = dist(engine);
        return CPPY_ERROR_t::Ok;
    }

    /* Normal distribution.
     *
     * mu is the mean, and sigma is the standard deviation.
     */
    template <typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
    CPPY_ERROR_t normalvariate(T mu, T sigma, T* const result)
    {
        std::normal_distribution<T> dist(mu, sigma);
        *result = dist(engine);
        return CPPY_ERROR_t::Ok;
    }

    /* Shuffle list x in place, and return None.
     */
    template <class Iterable>
    CPPY_ERROR_t shuffle(Iterable first, Iterable last)
    {
        std::shuffle(first, last, engine);
        return CPPY_ERROR_t::Ok;
    }

    /* Choose a random element from a non-empty sequence.
     */
    template <class Iterable>
    CPPY_ERROR_t choice(Iterable first, Iterable last, typename std::iterator_traits<Iterable>::value_type* result)
    {
        if (first == last)
            return CPPY_ERROR_t::IndexError;

        using iterator_category = typename std::iterator_traits<Iterable>::iterator_category;
        if constexpr (std::is_base_of_v<std::random_access_iterator_tag, iterator_category>)
        {
            const size_t length = std::distance(first, last);
            std::uniform_int_distribution<size_t> dist(0, length - 1);
            const size_t random_idx = dist(engine);
            *result = *(first + random_idx);
        }
        else
        {
            *result = *first;
            size_t count = 1;
            for (Iterable it = std::next(first); it != last; ++it, ++count)
            {
                std::uniform_int_distribution<size_t> dist(0, count);
                if (dist(engine) == 0)
                {
                    *result = *it;
                }
            }
        }
        return CPPY_ERROR_t::Ok;
    }
};
