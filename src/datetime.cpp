#include "cppy/datetime.h"


CPPY_API CPPY_ERROR_t CPPY_DATETIME_now(std::chrono::steady_clock::time_point* const time_point) {
    *time_point = std::chrono::steady_clock::now();
    return CPPY_ERROR_t::Ok;
}
