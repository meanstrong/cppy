#pragma once

#include <ios>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "cppy/exception.h"
#include "cppy/internal/declare.h"

// ===== StringIO =====

CPPY_API CPPY_ERROR_t CPPY_IO_StringIO_init(std::stringstream* strm, const std::string& initial_value = "");

CPPY_API CPPY_ERROR_t CPPY_IO_StringIO_read(std::stringstream* strm, std::string* const result, size_t size = -1);

CPPY_API CPPY_ERROR_t
CPPY_IO_StringIO_readline(std::stringstream* strm, std::string* const result, size_t size = -1);

CPPY_API CPPY_ERROR_t
CPPY_IO_StringIO_readlines(std::stringstream* strm, std::vector<std::string>* const result);

CPPY_API CPPY_ERROR_t CPPY_IO_StringIO_write(std::stringstream* strm, const std::string& s);

CPPY_API CPPY_ERROR_t
CPPY_IO_StringIO_writelines(std::stringstream* strm, const std::vector<std::string>& lines);

CPPY_API CPPY_ERROR_t CPPY_IO_StringIO_getvalue(std::stringstream* strm, std::string* const result);

CPPY_API CPPY_ERROR_t CPPY_IO_StringIO_seek(std::stringstream* strm, long pos, int whence);

CPPY_API CPPY_ERROR_t CPPY_IO_StringIO_tell(std::stringstream* strm, long* const result);

CPPY_API CPPY_ERROR_t CPPY_IO_StringIO_truncate(std::stringstream* strm, long size = -1);

CPPY_API CPPY_ERROR_t CPPY_IO_StringIO_close(std::stringstream* strm);

CPPY_API CPPY_ERROR_t CPPY_IO_StringIO_flush(std::stringstream* strm);

// ===== FileIO =====

CPPY_API CPPY_ERROR_t CPPY_IO_FileIO_open(std::fstream* file,
                                          const std::string& filename,
                                          std::ios_base::openmode mode = std::ios_base::in);

CPPY_API CPPY_ERROR_t CPPY_IO_FileIO_close(std::fstream* file);

CPPY_API CPPY_ERROR_t CPPY_IO_FileIO_flush(std::fstream* file);

CPPY_API CPPY_ERROR_t CPPY_IO_FileIO_read(std::fstream* file, std::string* const result, size_t size = -1);

CPPY_API CPPY_ERROR_t
CPPY_IO_FileIO_readline(std::fstream* file, std::string* const result, size_t size = -1);

CPPY_API CPPY_ERROR_t CPPY_IO_FileIO_readlines(std::fstream* file, std::vector<std::string>* const result);

CPPY_API CPPY_ERROR_t CPPY_IO_FileIO_write(std::fstream* file, const std::string& s);

CPPY_API CPPY_ERROR_t
CPPY_IO_FileIO_writelines(std::fstream* file, const std::vector<std::string>& lines);

CPPY_API CPPY_ERROR_t CPPY_IO_FileIO_seek(std::fstream* file, long pos, int whence);

CPPY_API CPPY_ERROR_t CPPY_IO_FileIO_tell(std::fstream* file, long* const result);

CPPY_API CPPY_ERROR_t CPPY_IO_FileIO_truncate(std::fstream* file, long size = -1);

// ===== BytesIO =====

CPPY_API CPPY_ERROR_t CPPY_IO_BytesIO_init(std::vector<char>* buf, const std::vector<char>& initial_bytes = {});

CPPY_API CPPY_ERROR_t
CPPY_IO_BytesIO_read(std::vector<char>* buf, size_t* pos, std::vector<char>* const result, size_t size = -1);

CPPY_API CPPY_ERROR_t
CPPY_IO_BytesIO_write(std::vector<char>* buf, size_t* pos, const std::vector<char>& data);

CPPY_API CPPY_ERROR_t CPPY_IO_BytesIO_getvalue(std::vector<char>* buf, std::vector<char>* const result);

CPPY_API CPPY_ERROR_t CPPY_IO_BytesIO_seek(std::vector<char>* buf, size_t* pos, long offset, int whence);

CPPY_API CPPY_ERROR_t CPPY_IO_BytesIO_tell(std::vector<char>* buf, size_t* pos, long* const result);

CPPY_API CPPY_ERROR_t CPPY_IO_BytesIO_truncate(std::vector<char>* buf, size_t* pos, long size = -1);

// ===== Helper: mode string to openmode =====

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
