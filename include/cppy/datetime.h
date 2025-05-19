#ifndef CPPY_DATETIME_H
#define CPPY_DATETIME_H

#include <chrono>

#include "cppy/internal/declare.h"
#include "cppy/exception.h"

/* Construct a datetime
*/
CPPY_API CPPY_ERROR_t CPPY_DATETIME_now(std::chrono::steady_clock::time_point* const time_point);

template <typename duration>
CPPY_API CPPY_ERROR_t CPPY_DATETIME_duration(const std::chrono::steady_clock::time_point& start, const std::chrono::steady_clock::time_point& end, typename duration::rep* const result) {
	*result = std::chrono::duration_cast<duration>(end - start).count();
	return CPPY_ERROR_t::Ok;
}

#endif // CPPY_DATETIME_H
