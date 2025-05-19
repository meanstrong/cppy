#include "cppy/platform.h"

CPPY_API CPPY_ERROR_t CPPY_PLATFORM_os_info(std::string* const result) {
#if defined(WIN32) | defined(_WIN64)
	return CPPY_ERROR_t::NotImplementedError;
#elif __linux__
	FILE* fp = fopen("/proc/version", "r");
	if (NULL == fp)
		return PyException::FileNotFoundError;
	char szTest[1000] = { 0 };
	while (!feof(fp)) {
		memset(szTest, 0, sizeof(szTest));
		fgets(szTest, sizeof(szTest) - 1, fp);
		*result += szTest;
	}
	fclose(fp);
	return PyException::Ok;
#else /*not support*/
#error "process info doesn't support this platform"
#endif
}

CPPY_API CPPY_ERROR_t CPPY_PLATFORM_cpu_percent(double* const percent, int interval) {
#if defined(WIN32) | defined(_WIN64)
	*percent = cppy::internal::get_cpu_usage();
	if (interval > 0)
	{
		Sleep(interval * 1000);
		*percent = cppy::internal::get_cpu_usage();
	}
	return CPPY_ERROR_t::Ok;
#elif __linux__

	FILE* fp = fopen("/proc/cpuinfo", "r");
	if (NULL == fp)
		return PyException::FileNotFoundError;
	char szTest[1000] = { 0 };
	while (!feof(fp)) {
		memset(szTest, 0, sizeof(szTest));
		fgets(szTest, sizeof(szTest) - 1, fp);
		*result += szTest;
	}
	fclose(fp);
	return PyException::Ok;
#else /*not support*/
#error "process info doesn't support this platform"
#endif
}

CPPY_API CPPY_ERROR_t CPPY_PLATFORM_memory(DWORDLONG* total, DWORDLONG* available) {
#if defined(WIN32) | defined(_WIN64)
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);
	*total = memInfo.ullTotalPhys;
	*available = memInfo.ullAvailPhys;
	return CPPY_ERROR_t::Ok;
#elif __linux__
	FILE* fp = fopen("/proc/meminfo", "r");
	if (NULL == fp)
		return PyException::FileNotFoundError;
	char szTest[1000] = { 0 };
	while (!feof(fp)) {
		memset(szTest, 0, sizeof(szTest));
		fgets(szTest, sizeof(szTest) - 1, fp);
		*result += szTest;
	}
	fclose(fp);
	return PyException::Ok;
#else /*not support*/
#error "process info doesn't support this platform"
#endif
}
