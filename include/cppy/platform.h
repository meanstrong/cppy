#include "cppy/exception.h"
#include "cppy/internal/declare.h"

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

#if defined(WIN32) | defined(_WIN64)
#elif __linux__
PyException CPPY_PLATFORM_os_info(std::string *const result) {
  FILE *fp = fopen("/proc/version", "r");
  if (NULL == fp)
    return PyException::FileNotFoundError;
  char szTest[1000] = {0};
  while (!feof(fp)) {
    memset(szTest, 0, sizeof(szTest));
    fgets(szTest, sizeof(szTest) - 1, fp);
    *result += szTest;
  }
  fclose(fp);
  return PyException::Ok;
}
#else /*not support*/
#error "process info doesn't support this platform"
#endif

PyException CPPY_PLATFORM_cpu_info(std::string* const result) {
#if defined(WIN32) | defined(_WIN64)
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    DWORDLONG totalPhysMem = memInfo.ullTotalPhys;

    return totalPhysMem;
#elif __linux__

  FILE *fp = fopen("/proc/cpuinfo", "r");
  if (NULL == fp)
    return PyException::FileNotFoundError;
  char szTest[1000] = {0};
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

#if defined(WIN32) | defined(_WIN64)
#elif __linux__
PyException CPPY_PLATFORM_memory_info(std::string *const result) {
  FILE *fp = fopen("/proc/meminfo", "r");
  if (NULL == fp)
    return PyException::FileNotFoundError;
  char szTest[1000] = {0};
  while (!feof(fp)) {
    memset(szTest, 0, sizeof(szTest));
    fgets(szTest, sizeof(szTest) - 1, fp);
    *result += szTest;
  }
  fclose(fp);
  return PyException::Ok;
}
#else /*not support*/
#error "process info doesn't support this platform"
#endif
