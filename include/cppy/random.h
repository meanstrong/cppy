#pragma once

#include <random>
#include <vector>
#include <algorithm>
#include <chrono>

#include "cppy/internal/declare.h"
#include "cppy/exception.h"

/* Random number generator base class used by bound module functions.
*/
class CPPY_API CPPY_RANDOM_Random {
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
	template<typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>
	CPPY_ERROR_t randint(T a, T b, T* const result) {
		if (a > b)
			return CPPY_ERROR_t::ValueError;
		std::uniform_int_distribution<T> dist(a, b);
		*result = dist(engine);
		return CPPY_ERROR_t::Ok;
	}

	/* x in the interval [0, 1).
	*/
	CPPY_ERROR_t random(double* const result) {
		std::uniform_real_distribution<double> dist(0.0, 1.0);
		*result = dist(engine);
		return CPPY_ERROR_t::Ok;
	}

	/* Get a random number in the range [a, b) or [a, b] depending on rounding.
	*/
	template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
	CPPY_ERROR_t uniform(T a, T b, T* const result) {
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
	template<typename T, std::enable_if_t<std::is_floating_point_v<T>, int> = 0>
	CPPY_ERROR_t normalvariate(T mu, T sigma, T* const result) {
		std::normal_distribution<double> dist(mu, sigma);
		*result = dist(engine);
		return CPPY_ERROR_t::Ok;
	}


	/* Shuffle list x in place, and return None.
	*/
	template<class Iteratable>
	CPPY_ERROR_t shuffle(Iteratable begin, Iteratable end) {
		std::shuffle(begin, end, engine);
		return CPPY_ERROR_t::Ok;
	}
};
