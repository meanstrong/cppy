#include "cppy/io.h"

CPPY_ERROR_t CPPY_IO_StringIO_init(CPPY_IO_StringIO* handle, const std::string& initial_value, bool readable, bool writable)
{
    handle->closed = false;
    handle->readable = readable;
    handle->writable = writable;

    if (writable)
    {
        handle->stream << initial_value;
    }
    else if (readable)
    {
        handle->stream.str(initial_value);
    }

    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_StringIO_close(CPPY_IO_StringIO* handle)
{
    handle->closed = true;
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_StringIO_flush(CPPY_IO_StringIO* handle)
{
    handle->stream.flush();
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_StringIO_read(CPPY_IO_StringIO* handle, std::string* const result, size_t size)
{
    CPPY_ASSERT(!handle->closed) << "ValueError: I/O operation on closed file.";
    CPPY_ASSERT(handle->readable) << "io.UnsupportedOperation: not readable";

    if (size == static_cast<size_t>(-1))
    {
        *result = handle->stream.str().substr(handle->stream.tellg());
        handle->stream.seekg(0, std::ios::end);
    }
    else
    {
        result->resize(size);
        if (!handle->stream.read(&result->front(), size))
            return CPPY_ERROR_t::EOFError;
        result->resize(handle->stream.gcount());
    }
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_StringIO_readline(CPPY_IO_StringIO* handle, std::string* const result, size_t size)
{
    CPPY_ASSERT(!handle->closed) << "ValueError: I/O operation on closed file.";
    CPPY_ASSERT(handle->readable) << "io.UnsupportedOperation: not readable";

    if (size == static_cast<size_t>(-1))
    {
        if (!std::getline(handle->stream, *result))
            return CPPY_ERROR_t::EOFError;
    }
    else
    {
        result->resize(size);
        if (!handle->stream.getline(&result->front(), size))
            return CPPY_ERROR_t::EOFError;
        result->resize(handle->stream.gcount());
    }
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_StringIO_readlines(CPPY_IO_StringIO* handle, std::vector<std::string>* const result)
{
    CPPY_ASSERT(!handle->closed) << "ValueError: I/O operation on closed file.";
    CPPY_ASSERT(handle->readable) << "io.UnsupportedOperation: not readable";

    std::string line;
    while (std::getline(handle->stream, line))
    {
        result->push_back(line);
    }
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_StringIO_write(CPPY_IO_StringIO* handle, const std::string& s)
{
    CPPY_ASSERT(!handle->closed) << "ValueError: I/O operation on closed file.";
    CPPY_ASSERT(handle->writable) << "io.UnsupportedOperation: not writable";

    handle->stream << s;
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_StringIO_writelines(CPPY_IO_StringIO* handle, const std::vector<std::string>& lines)
{
    CPPY_ASSERT(!handle->closed) << "ValueError: I/O operation on closed file.";
    CPPY_ASSERT(handle->writable) << "io.UnsupportedOperation: not writable";

    for (const auto& line : lines)
    {
        handle->stream << line;
    }
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_StringIO_getvalue(CPPY_IO_StringIO* handle, std::string* const result)
{
    *result = handle->stream.str();
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_FileIO_init(CPPY_IO_FileIO* handle, const std::string& filename, std::ios_base::openmode mode)
{
    handle->closed = false;
    handle->mode = mode;
    handle->file.open(filename, mode);

    CPPY_ASSERT(handle->file.is_open()) << "FileNotFoundError: No such file or directory: '" << filename << "'";
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_FileIO_close(CPPY_IO_FileIO* handle)
{
    CPPY_ASSERT(!handle->closed) << "ValueError: I/O operation on closed file.";
    handle->file.close();
    handle->closed = true;
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_FileIO_flush(CPPY_IO_FileIO* handle)
{
    handle->file.flush();
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_FileIO_read(CPPY_IO_FileIO* handle, std::string* const result, size_t size)
{
    CPPY_ASSERT(!handle->closed) << "ValueError: I/O operation on closed file.";
    CPPY_ASSERT(handle->mode & std::ios_base::in) << "io.UnsupportedOperation: not readable";

    if (size == static_cast<size_t>(-1))
    {
        std::stringstream ss;
        ss << handle->file.rdbuf();
        *result = ss.str();
    }
    else
    {
        result->resize(size);
        if (!handle->file.read(&result->front(), size))
            return CPPY_ERROR_t::EOFError;
        result->resize(handle->file.gcount());
    }
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_FileIO_readline(CPPY_IO_FileIO* handle, std::string* const result, size_t size)
{
    CPPY_ASSERT(!handle->closed) << "ValueError: I/O operation on closed file.";
    CPPY_ASSERT(handle->mode & std::ios_base::in) << "io.UnsupportedOperation: not readable";

    if (size == static_cast<size_t>(-1))
    {
        if (!std::getline(handle->file, *result))
            return CPPY_ERROR_t::EOFError;
    }
    else
    {
        result->resize(size);
        if (!handle->file.getline(&result->front(), size))
            return CPPY_ERROR_t::EOFError;
        result->resize(handle->file.gcount());
    }
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_FileIO_readlines(CPPY_IO_FileIO* handle, std::vector<std::string>* const result)
{
    CPPY_ASSERT(!handle->closed) << "ValueError: I/O operation on closed file.";
    CPPY_ASSERT(handle->mode & std::ios_base::in) << "io.UnsupportedOperation: not readable";

    std::string line;
    while (std::getline(handle->file, line))
    {
        result->push_back(line);
    }
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_FileIO_write(CPPY_IO_FileIO* handle, const std::string& s)
{
    CPPY_ASSERT(!handle->closed) << "ValueError: I/O operation on closed file.";
    CPPY_ASSERT(handle->mode & (std::ios_base::out | std::ios_base::app)) << "io.UnsupportedOperation: not writable";

    handle->file << s;
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_FileIO_writelines(CPPY_IO_FileIO* handle, const std::vector<std::string>& lines)
{
    CPPY_ASSERT(!handle->closed) << "ValueError: I/O operation on closed file.";
    CPPY_ASSERT(handle->mode & (std::ios_base::out | std::ios_base::app)) << "io.UnsupportedOperation: not writable";

    for (const auto& line : lines)
    {
        handle->file << line;
    }
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_BytesIO_init(CPPY_IO_BytesIO* handle, const std::vector<char>& initial_bytes, bool readable, bool writable)
{
    handle->buffer = initial_bytes;
    handle->position = 0;
    handle->closed = false;
    handle->readable = readable;
    handle->writable = writable;
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_BytesIO_close(CPPY_IO_BytesIO* handle)
{
    handle->closed = true;
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_BytesIO_read(CPPY_IO_BytesIO* handle, std::vector<char>* const result, size_t size)
{
    CPPY_ASSERT(!handle->closed) << "ValueError: I/O operation on closed file.";
    CPPY_ASSERT(handle->readable) << "io.UnsupportedOperation: not readable";

    if (size == static_cast<size_t>(-1) || handle->position + size > handle->buffer.size())
    {
        size = handle->buffer.size() - handle->position;
    }

    result->resize(size);
    std::copy(handle->buffer.begin() + handle->position,
              handle->buffer.begin() + handle->position + size,
              result->begin());
    handle->position += size;

    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_BytesIO_write(CPPY_IO_BytesIO* handle, const std::vector<char>& data)
{
    CPPY_ASSERT(!handle->closed) << "ValueError: I/O operation on closed file.";
    CPPY_ASSERT(handle->writable) << "io.UnsupportedOperation: not writable";

    if (handle->position + data.size() > handle->buffer.size())
    {
        handle->buffer.resize(handle->position + data.size());
    }

    std::copy(data.begin(), data.end(), handle->buffer.begin() + handle->position);
    handle->position += data.size();

    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_BytesIO_getvalue(CPPY_IO_BytesIO* handle, std::vector<char>* const result)
{
    *result = handle->buffer;
    return CPPY_ERROR_t::Ok;
}
