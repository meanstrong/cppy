#include "cppy/random.h"


CPPY_RANDOM_Random::CPPY_RANDOM_Random() {
	seed(std::chrono::system_clock::now().time_since_epoch().count());
}

CPPY_RANDOM_Random::CPPY_RANDOM_Random(unsigned int x) {
	seed(x);
}

void CPPY_RANDOM_Random::seed(unsigned int a) {
	engine.seed(a);
}