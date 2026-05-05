#pragma once

#include <ios>
#include <string>
#include <vector>

#include "cppy/exception.h"
#include "cppy/internal/declare.h"

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct CPPY_IO_StringIO
{
    std::stringstream stream;
    bool closed;
    bool readable;
    bool writable;
};

struct CPPY_IO_FileIO
{
    std::fstream file;
    bool closed;
    std::ios_base::openmode mode;
};

struct CPPY_IO_BytesIO
{
    std::vector<char> buffer;
    size_t position;
    bool closed;
    bool readable;
    bool writable;
};

CPPY_API constexpr std::ios_base::openmode CPPY_IO_mode(const char c)
{
    switch (c)
    {
    case 'r':
        return std::ios_base::in;
    case 'w':
        return std::ios_base::out | std::ios_base::trunc;
    case 'a':
        return std::ios_base::out | std::ios_base::app;
    case '+':
        return std::ios_base::in | std::ios_base::out;
    case 'b':
        return std::ios_base::binary;
    default:
        return std::ios_base::openmode{};
    }
}

template <typename... Args>
constexpr std::ios_base::openmode CPPY_IO_mode(Args... args)
{
    return (CPPY_IO_mode(args) | ...);
};

CPPY_API CPPY_ERROR_t CPPY_IO_StringIO_init(CPPY_IO_StringIO* handle,
                                            const std::string& initial_value = "",
                                            bool readable = true,
                                            bool writable = true);
CPPY_API CPPY_ERROR_t CPPY_IO_StringIO_close(CPPY_IO_StringIO* handle);
CPPY_API CPPY_ERROR_t CPPY_IO_StringIO_flush(CPPY_IO_StringIO* handle);
CPPY_API CPPY_ERROR_t CPPY_IO_StringIO_read(CPPY_IO_StringIO* handle, std::string* const result, size_t size = -1);
CPPY_API CPPY_ERROR_t CPPY_IO_StringIO_readline(CPPY_IO_StringIO* handle, std::string* const result, size_t size = -1);
CPPY_API CPPY_ERROR_t CPPY_IO_StringIO_readlines(CPPY_IO_StringIO* handle, std::vector<std::string>* const result);
CPPY_API CPPY_ERROR_t CPPY_IO_StringIO_write(CPPY_IO_StringIO* handle, const std::string& s);
CPPY_API CPPY_ERROR_t CPPY_IO_StringIO_writelines(CPPY_IO_StringIO* handle, const std::vector<std::string>& lines);
CPPY_API CPPY_ERROR_t CPPY_IO_StringIO_getvalue(CPPY_IO_StringIO* handle, std::string* const result);

CPPY_API CPPY_ERROR_t CPPY_IO_FileIO_init(CPPY_IO_FileIO* handle,
                                          const std::string& filename,
                                          std::ios_base::openmode mode = std::ios_base::in);
CPPY_API CPPY_ERROR_t CPPY_IO_FileIO_close(CPPY_IO_FileIO* handle);
CPPY_API CPPY_ERROR_t CPPY_IO_FileIO_flush(CPPY_IO_FileIO* handle);
CPPY_API CPPY_ERROR_t CPPY_IO_FileIO_read(CPPY_IO_FileIO* handle, std::string* const result, size_t size = -1);
CPPY_API CPPY_ERROR_t CPPY_IO_FileIO_readline(CPPY_IO_FileIO* handle, std::string* const result, size_t size = -1);
CPPY_API CPPY_ERROR_t CPPY_IO_FileIO_readlines(CPPY_IO_FileIO* handle, std::vector<std::string>* const result);
CPPY_API CPPY_ERROR_t CPPY_IO_FileIO_write(CPPY_IO_FileIO* handle, const std::string& s);
CPPY_API CPPY_ERROR_t CPPY_IO_FileIO_writelines(CPPY_IO_FileIO* handle, const std::vector<std::string>& lines);

CPPY_API CPPY_ERROR_t CPPY_IO_BytesIO_init(CPPY_IO_BytesIO* handle,
                                           const std::vector<char>& initial_bytes = {},
                                           bool readable = true,
                                           bool writable = true);
CPPY_API CPPY_ERROR_t CPPY_IO_BytesIO_close(CPPY_IO_BytesIO* handle);
CPPY_API CPPY_ERROR_t CPPY_IO_BytesIO_read(CPPY_IO_BytesIO* handle, std::vector<char>* const result, size_t size = -1);
CPPY_API CPPY_ERROR_t CPPY_IO_BytesIO_write(CPPY_IO_BytesIO* handle, const std::vector<char>& data);
CPPY_API CPPY_ERROR_t CPPY_IO_BytesIO_getvalue(CPPY_IO_BytesIO* handle, std::vector<char>* const result);
