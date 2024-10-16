#ifndef CPPY_INT_H
#define CPPY_INT_H

#include <string>

#include "cppy/internal/declare.h"
#include "cppy/exception.h"


CPPY_API PyException CPPY_INT_init(const std::string& str, int* const result);


#endif // CPPY_INT_H
