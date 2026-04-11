#pragma once

#pragma warning(disable : 4251)

#ifndef CPPY_API

#ifdef _MSC_VER
#if defined(CPPY_CREATE_SHARED_LIBRARY)
#define CPPY_API __declspec(dllexport)
#elif defined(CPPY_LINKED_AS_SHARED_LIBRARY)
#define CPPY_API __declspec(dllimport)
#else
#define CPPY_API
#endif  // CREATE_SHARED_LIBRARY
#else   // non windows
#define CPPY_API __attribute__((visibility("default")))
#endif  // _MSC_VER

#endif  // CPPY_API
