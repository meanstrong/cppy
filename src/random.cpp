#include "cppy/random.h"


CPPY_API CPPY_ERROR_t CPPY_RANDOM_init(CPPY_Random* const random) {
    random->engine.seed(static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()));
    return CPPY_ERROR_t::Ok;
}

CPPY_API CPPY_ERROR_t CPPY_RANDOM_init(CPPY_Random* const random, unsigned int x) {
    random->engine.seed(x);
    return CPPY_ERROR_t::Ok;
}

CPPY_API CPPY_ERROR_t  CPPY_RANDOM_seed(CPPY_Random* const random, unsigned int a) {
    random->engine.seed(a);
    return CPPY_ERROR_t::Ok;
}
