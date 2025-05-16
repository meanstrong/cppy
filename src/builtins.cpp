#include "cppy/builtins.h"


CPPY_API PyException CPPY_BUILTINS_linspace(double start, double end, int num, double result[], bool endpoint) {
    if (num < 1)
        return PyException::Ok;

    result[0] = start;
    if (num == 1)
        return PyException::Ok;

    if (num == 2 && endpoint)
    {
        result[1] = end;
        return PyException::Ok;
    }

    double step = endpoint ? (end - start) / (num - 1) : (end - start) / num;
    for (int i = 1; i < num - 1; ++i)
        result[i] = result[i-1] + step;
    result[num - 1] = endpoint ? end : result[num - 2] + step;
    return PyException::Ok;
}
