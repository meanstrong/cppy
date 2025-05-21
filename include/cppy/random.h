#pragma once

#include <random>

#include "cppy/internal/declare.h"
#include "cppy/exception.h"

/* random() -> x in the interval [0, 1).
*/
CPPY_API CPPY_ERROR_t CPPY_RANDOM_random(double start, double end, double* const result);

/* Return random integer in range [a, b], including both end points.
*/
CPPY_API CPPY_ERROR_t CPPY_RANDOM_randint(int start, int end, int* const result);