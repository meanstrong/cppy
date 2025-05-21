#include "cppy/random.h"


CPPY_API CPPY_ERROR_t CPPY_RANDOM_random(double start, double end, double* const result) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<double> dis(minValue, maxValue);

    *result = dis(gen);
    return CPPY_ERROR_t::Ok;
}

CPPY_API CPPY_ERROR_t CPPY_RANDOM_randint(int start, int end, int* const result) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(minValue, maxValue);

    *result = dis(gen);
    return CPPY_ERROR_t::Ok;
}
