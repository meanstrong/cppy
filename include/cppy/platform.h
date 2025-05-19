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
		double get_cpu_usage() {
			static FILETIME prevIdleTime, prevKernelTime, prevUserTime;
			FILETIME idleTime, kernelTime, userTime;

			// 获取当前系统的空闲时间、内核态时间和用户态时间
			if (!GetSystemTimes(&idleTime, &kernelTime, &userTime)) {
				return -1;
			}

			ULONGLONG prevIdle = ((ULONGLONG)prevIdleTime.dwHighDateTime << 32) | prevIdleTime.dwLowDateTime;
			ULONGLONG idle = ((ULONGLONG)idleTime.dwHighDateTime << 32) | idleTime.dwLowDateTime;
			ULONGLONG prevKernel = ((ULONGLONG)prevKernelTime.dwHighDateTime << 32) | prevKernelTime.dwLowDateTime;
			ULONGLONG kernel = ((ULONGLONG)kernelTime.dwHighDateTime << 32) | kernelTime.dwLowDateTime;
			ULONGLONG prevUser = ((ULONGLONG)prevUserTime.dwHighDateTime << 32) | prevUserTime.dwLowDateTime;
			ULONGLONG user = ((ULONGLONG)userTime.dwHighDateTime << 32) | userTime.dwLowDateTime;

			ULONGLONG totalPrev = prevIdle + prevKernel + prevUser;
			ULONGLONG total = idle + kernel + user;

			ULONGLONG totalDelta = total - totalPrev;
			ULONGLONG idleDelta = idle - prevIdle;

			double cpuUsage = 100.0 * (totalDelta - idleDelta) / totalDelta;

			// 更新上一次的时间
			prevIdleTime = idleTime;
			prevKernelTime = kernelTime;
			prevUserTime = userTime;

			return cpuUsage;
		}
	}
}
