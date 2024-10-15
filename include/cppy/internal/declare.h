#ifndef CPPY_INTERNAL_DECLARE_H
#define CPPY_INTERNAL_DECLARE_H

#ifndef CPPY_API

#ifdef _MSC_VER
#if defined(CPPY_CREATE_SHARED_LIBRARY)
#define CPPY_API __declspec(dllexport)
#elif defined(CPPY_LINKED_AS_SHARED_LIBRARY)
#define CPPY_API __declspec(dllimport)
#endif  // CREATE_SHARED_LIBRARY
#else   // non windows
#define CPPY_API __attribute__((visibility("default")))
#endif  // _MSC_VER

#endif  // CPPY_API

#ifndef CPPY_API
#define CPPY_API
#endif  // CPPY_API

#endif // CPPY_INTERNAL_DECLARE_H