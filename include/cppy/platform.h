#pragma once

#include <cstdint>
#include <string>

#include "cppy/exception.h"
#include "cppy/internal/declare.h"

CPPY_API CPPY_ERROR_t CPPY_PLATFORM_os_info(std::string* const result);

CPPY_API CPPY_ERROR_t CPPY_PLATFORM_cpu_percent(double* const percent, int interval = -1);

CPPY_API CPPY_ERROR_t CPPY_PLATFORM_memory(uint64_t* total, uint64_t* available);

#if defined(_WIN32) || defined(_WIN64)

#    pragma comment(lib, "pdh.lib")
#    include <Pdh.h>
#    include <Windows.h>

#elif __linux__

#    include <unistd.h>
#    include <cstdio>
#    include <cstdlib>
#    include <cstring>

#else /*not support*/
#    error "process info doesn't support this platform"
#endif
