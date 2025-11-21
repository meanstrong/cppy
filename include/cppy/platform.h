#pragma once

#if defined(WIN32) | defined(_WIN64)

#pragma comment(lib, "pdh.lib")
#include <Windows.h>
#include <Pdh.h>

#elif __linux__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#else /*not support*/
#error "process info doesn't support this platform"
#endif

#include <string>

#include "cppy/exception.h"
#include "cppy/internal/declare.h"

CPPY_API CPPY_ERROR_t CPPY_PLATFORM_os_info(std::string* const result);

CPPY_API CPPY_ERROR_t CPPY_PLATFORM_cpu_percent(double* const percent, int interval = -1);

CPPY_API CPPY_ERROR_t CPPY_PLATFORM_memory(DWORDLONG* total, DWORDLONG* available);

namespace cppy {
	namespace internal {
		double get_cpu_usage();
	}
}
