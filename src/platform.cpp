#include "cppy/platform.h"

#if defined(_WIN32)

CPPY_API CPPY_ERROR_t CPPY_PLATFORM_os_info(std::string* const result)
{
    OSVERSIONINFOEXA osvi = {0};
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEXA);
    GetVersionExA((OSVERSIONINFOA*)&osvi);

    char buffer[256];
    snprintf(buffer,
             sizeof(buffer),
             "Windows %d.%d.%d (SP %d.%d)",
             osvi.dwMajorVersion,
             osvi.dwMinorVersion,
             osvi.dwBuildNumber,
             osvi.wServicePackMajor,
             osvi.wServicePackMinor);
    *result = buffer;
    return CPPY_ERROR_t::Ok;
}

static void get_cpu_times(ULONGLONG* idle, ULONGLONG* kernel, ULONGLONG* user)
{
    FILETIME idleTime, kernelTime, userTime;
    GetSystemTimes(&idleTime, &kernelTime, &userTime);

    *idle = ((ULONGLONG)idleTime.dwHighDateTime << 32) | idleTime.dwLowDateTime;
    *kernel = ((ULONGLONG)kernelTime.dwHighDateTime << 32) | kernelTime.dwLowDateTime;
    *user = ((ULONGLONG)userTime.dwHighDateTime << 32) | userTime.dwLowDateTime;
}

CPPY_API CPPY_ERROR_t CPPY_PLATFORM_cpu_percent(double* const percent, int interval)
{
    ULONGLONG idle1, kernel1, user1;
    ULONGLONG idle2, kernel2, user2;

    get_cpu_times(&idle1, &kernel1, &user1);

    if (interval <= 0)
        interval = 1;
    Sleep(interval * 1000);

    get_cpu_times(&idle2, &kernel2, &user2);

    ULONGLONG total1 = idle1 + kernel1 + user1;
    ULONGLONG total2 = idle2 + kernel2 + user2;
    ULONGLONG idleDelta = idle2 - idle1;
    ULONGLONG totalDelta = total2 - total1;

    *percent = 100.0 * (totalDelta - idleDelta) / totalDelta;
    return CPPY_ERROR_t::Ok;
}

CPPY_API CPPY_ERROR_t CPPY_PLATFORM_memory(uint64_t* total, uint64_t* available)
{
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    *total = memInfo.ullTotalPhys;
    *available = memInfo.ullAvailPhys;
    return CPPY_ERROR_t::Ok;
}

#elif __linux__

static void read_file(const char* path, std::string* result)
{
    FILE* fp = fopen(path, "r");
    if (fp)
    {
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), fp))
        {
            *result += buffer;
        }
        fclose(fp);
    }
}

CPPY_API CPPY_ERROR_t CPPY_PLATFORM_os_info(std::string* const result)
{
    read_file("/proc/version", result);
    return CPPY_ERROR_t::Ok;
}

CPPY_API CPPY_ERROR_t CPPY_PLATFORM_memory(uint64_t* total, uint64_t* available)
{
    *total = 0;
    *available = 0;

    FILE* fp = fopen("/proc/meminfo", "r");
    if (!fp)
        return CPPY_ERROR_t::ValueError;

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp))
    {
        uint64_t value;
        if (sscanf(buffer, "MemTotal: %lu kB", &value) == 1)
            *total = value * 1024;
        else if (sscanf(buffer, "MemAvailable: %lu kB", &value) == 1)
            *available = value * 1024;
    }
    fclose(fp);
    return CPPY_ERROR_t::Ok;
}

CPPY_API CPPY_ERROR_t CPPY_PLATFORM_cpu_percent(double* const percent, int interval)
{
    FILE* fp1 = fopen("/proc/stat", "r");
    if (!fp1)
        return CPPY_ERROR_t::ValueError;

    unsigned long long user1, nice1, system1, idle1, iowait1, irq1, softirq1;
    char buffer[256];
    if (!fgets(buffer, sizeof(buffer), fp1))
    {
        fclose(fp1);
        return CPPY_ERROR_t::ValueError;
    }
    sscanf(buffer,
           "cpu  %llu %llu %llu %llu %llu %llu %llu",
           &user1,
           &nice1,
           &system1,
           &idle1,
           &iowait1,
           &irq1,
           &softirq1);
    fclose(fp1);

    if (interval <= 0)
        interval = 1;
    sleep(interval);

    FILE* fp2 = fopen("/proc/stat", "r");
    if (!fp2)
        return CPPY_ERROR_t::ValueError;

    unsigned long long user2, nice2, system2, idle2, iowait2, irq2, softirq2;
    if (!fgets(buffer, sizeof(buffer), fp2))
    {
        fclose(fp2);
        return CPPY_ERROR_t::ValueError;
    }
    sscanf(buffer,
           "cpu  %llu %llu %llu %llu %llu %llu %llu",
           &user2,
           &nice2,
           &system2,
           &idle2,
           &iowait2,
           &irq2,
           &softirq2);
    fclose(fp2);

    unsigned long long total1 = user1 + nice1 + system1 + idle1 + iowait1 + irq1 + softirq1;
    unsigned long long total2 = user2 + nice2 + system2 + idle2 + iowait2 + irq2 + softirq2;
    unsigned long long idle_delta = idle2 - idle1;
    unsigned long long total_delta = total2 - total1;

    *percent = 100.0 * (total_delta - idle_delta) / total_delta;
    return CPPY_ERROR_t::Ok;
}

#endif
