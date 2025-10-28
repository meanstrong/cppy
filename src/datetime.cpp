#include "cppy/datetime.h"


CPPY_API CPPY_ERROR_t CPPY_DATETIME_now(std::chrono::steady_clock::time_point* const now) {
	*now = std::chrono::steady_clock::now();
	return CPPY_ERROR_t::Ok;
}

CPPY_API CPPY_ERROR_t CPPY_DATETIME_now(std::time_t* const now) {
	*now = std::time(nullptr);
	return CPPY_ERROR_t::Ok;
}

CPPY_API CPPY_ERROR_t CPPY_DATETIME_strftime(const std::time_t& time, std::string* const strftime, const std::string& format) {
	std::tm local_time;
	if (localtime_s(&local_time, &time) != 0)
		return CPPY_ERROR_t::ValueError;
	char buffer[256];
	size_t len = std::strftime(buffer, sizeof(buffer), format.c_str(), &local_time);
	if (len == 0)
		return CPPY_ERROR_t::ValueError;
	*strftime = std::string(buffer, len);
	return CPPY_ERROR_t::Ok;
}
