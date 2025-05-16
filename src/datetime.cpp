#include "cppy/datetime.h"


CPPY_API PyException CPPY_DATETIME_now(std::chrono::steady_clock::time_point* const time_point) {
    *time_point = std::chrono::steady_clock::now();
    return PyException::Ok;
}
