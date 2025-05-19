#include "cppy/builtins.h"


CPPY_API CPPY_ERROR_t CPPY_BUILTINS_linspace(double start, double end, int num, double result[], bool endpoint) {
    if (num < 1)
        return CPPY_ERROR_t::Ok;

    result[0] = start;
    if (num == 1)
        return CPPY_ERROR_t::Ok;

    if (num == 2 && endpoint)
    {
        result[1] = end;
        return CPPY_ERROR_t::Ok;
    }

    double step = endpoint ? (end - start) / (num - 1) : (end - start) / num;
    for (int i = 1; i < num - 1; ++i)
        result[i] = result[i-1] + step;
    result[num - 1] = endpoint ? end : result[num - 2] + step;
    return CPPY_ERROR_t::Ok;
}
