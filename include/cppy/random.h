#pragma once

#include <random>

#include "cppy/internal/declare.h"
#include "cppy/exception.h"

/* random() -> x in the interval [0, 1).
*/
template <typename T>
CPPY_API CPPY_ERROR_t CPPY_RANDOM_random(T start, T end, T* const result)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<T> dis(start, end);

	*result = dis(gen);
	return CPPY_ERROR_t::Ok;
}

/* Return random integer in range [a, b], including both end points.
*/
template <typename T>
CPPY_API CPPY_ERROR_t CPPY_RANDOM_randint(T start, T end, T* const result)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<T> dis(start, end);

	*result = dis(gen);
	return CPPY_ERROR_t::Ok;
}