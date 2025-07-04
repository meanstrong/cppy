#pragma once

#include <chrono>
#include <ctime>

#include "cppy/internal/declare.h"
#include "cppy/exception.h"

/* Construct a datetime
*/
CPPY_API CPPY_ERROR_t CPPY_DATETIME_now(std::chrono::steady_clock::time_point* const now);

CPPY_API CPPY_ERROR_t CPPY_DATETIME_now(std::time_t* const now);

template <typename duration>
CPPY_API CPPY_ERROR_t CPPY_DATETIME_duration(const std::chrono::steady_clock::time_point& start, const std::chrono::steady_clock::time_point& end, typename duration::rep* const result) {
	*result = std::chrono::duration_cast<duration>(end - start).count();
	return CPPY_ERROR_t::Ok;
}

CPPY_API CPPY_ERROR_t CPPY_DATETIME_strftime(const std::time_t& time, std::string* const strftime, const std::string& format="%Y-%m-%d %H:%M:%S");
