#include "cppy/io.h"

// ====================================================================
// StringIO
// ====================================================================

CPPY_ERROR_t CPPY_IO_StringIO_init(std::stringstream* strm, const std::string& initial_value)
{
    strm->str(initial_value);
    strm->clear();
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_StringIO_read(std::stringstream* strm, std::string* const result, size_t size)
{
    if (size == static_cast<size_t>(-1))
    {
        auto pos = strm->tellg();
        std::string content = strm->str();
        if (pos < 0 || pos >= static_cast<std::streampos>(content.size()))
        {
            result->clear();
        }
        else
        {
            *result = content.substr(static_cast<size_t>(pos));
        }
        strm->seekg(0, std::ios::end);
    }
    else
    {
        result->resize(size);
        if (!strm->read(&result->front(), size))
        {
            size_t gcount = static_cast<size_t>(strm->gcount());
            if (gcount == 0)
                return CPPY_ERROR_t::EOFError;
            result->resize(gcount);
        }
    }
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_StringIO_readline(std::stringstream* strm, std::string* const result, size_t size)
{
    if (size == static_cast<size_t>(-1))
    {
        if (!std::getline(*strm, *result))
            return CPPY_ERROR_t::EOFError;
    }
    else
    {
        result->resize(size);
        if (!strm->getline(&result->front(), size))
        {
            size_t gcount = static_cast<size_t>(strm->gcount());
            if (gcount == 0)
                return CPPY_ERROR_t::EOFError;
            result->resize(gcount);
        }
    }
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_StringIO_readlines(std::stringstream* strm, std::vector<std::string>* const result)
{
    std::string line;
    while (std::getline(*strm, line))
    {
        result->push_back(line);
    }
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_StringIO_write(std::stringstream* strm, const std::string& s)
{
    *strm << s;
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_StringIO_writelines(std::stringstream* strm, const std::vector<std::string>& lines)
{
    for (const auto& line : lines)
    {
        *strm << line;
    }
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_StringIO_getvalue(std::stringstream* strm, std::string* const result)
{
    *result = strm->str();
    return CPPY_ERROR_t::Ok;
}

static constexpr std::ios_base::seekdir whence_map[] = {
    std::ios::beg, std::ios::cur, std::ios::end};

CPPY_ERROR_t CPPY_IO_StringIO_seek(std::stringstream* strm, long pos, int whence)
{
    if (whence < 0 || whence > 2)
        return CPPY_ERROR_t::ValueError;
    strm->clear();
    strm->seekg(pos, whence_map[whence]);
    strm->seekp(pos, whence_map[whence]);
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_StringIO_tell(std::stringstream* strm, long* const result)
{
    *result = static_cast<long>(strm->tellg());
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_StringIO_truncate(std::stringstream* strm, long size)
{
    auto old_pos = strm->tellg();
    std::string content = strm->str();
    if (size == -1)
        size = static_cast<long>(old_pos);
    if (size < 0)
        size = 0;
    if (static_cast<size_t>(size) < content.size())
    {
        content.resize(static_cast<size_t>(size));
        strm->str(content);
        strm->clear();
        if (old_pos > size)
            strm->seekg(size);
        else if (old_pos >= 0)
            strm->seekg(old_pos);
    }
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_StringIO_close(std::stringstream* /*strm*/)
{
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_StringIO_flush(std::stringstream* strm)
{
    strm->flush();
    return CPPY_ERROR_t::Ok;
}

// ====================================================================
// FileIO
// ====================================================================

CPPY_ERROR_t CPPY_IO_FileIO_open(std::fstream* file,
                                  const std::string& filename,
                                  std::ios_base::openmode mode)
{
    file->open(filename, mode);
    if (!file->is_open())
        return CPPY_ERROR_t::ValueError;
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_FileIO_close(std::fstream* file)
{
    file->close();
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_FileIO_flush(std::fstream* file)
{
    file->flush();
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_FileIO_read(std::fstream* file, std::string* const result, size_t size)
{
    if (size == static_cast<size_t>(-1))
    {
        std::stringstream ss;
        ss << file->rdbuf();
        *result = ss.str();
    }
    else
    {
        result->resize(size);
        if (!file->read(&result->front(), size))
        {
            size_t gcount = static_cast<size_t>(file->gcount());
            if (gcount == 0)
                return CPPY_ERROR_t::EOFError;
            result->resize(gcount);
        }
    }
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_FileIO_readline(std::fstream* file, std::string* const result, size_t size)
{
    if (size == static_cast<size_t>(-1))
    {
        if (!std::getline(*file, *result))
            return CPPY_ERROR_t::EOFError;
    }
    else
    {
        result->resize(size);
        if (!file->getline(&result->front(), size))
        {
            size_t gcount = static_cast<size_t>(file->gcount());
            if (gcount == 0)
                return CPPY_ERROR_t::EOFError;
            result->resize(gcount);
        }
    }
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_FileIO_readlines(std::fstream* file, std::vector<std::string>* const result)
{
    std::string line;
    while (std::getline(*file, line))
    {
        result->push_back(line);
    }
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_FileIO_write(std::fstream* file, const std::string& s)
{
    *file << s;
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_FileIO_writelines(std::fstream* file, const std::vector<std::string>& lines)
{
    for (const auto& line : lines)
    {
        *file << line;
    }
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_FileIO_seek(std::fstream* file, long pos, int whence)
{
    if (whence < 0 || whence > 2)
        return CPPY_ERROR_t::ValueError;
    file->clear();
    file->seekg(pos, whence_map[whence]);
    file->seekp(pos, whence_map[whence]);
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_FileIO_tell(std::fstream* file, long* const result)
{
    *result = static_cast<long>(file->tellg());
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_FileIO_truncate(std::fstream* file, long size)
{
    // fstream lacks a path-less truncate; needs redesign to store filename
    (void)file;
    (void)size;
    return CPPY_ERROR_t::NotImplementedError;
}

// ====================================================================
// BytesIO
// ====================================================================

CPPY_ERROR_t CPPY_IO_BytesIO_init(std::vector<char>* buf, const std::vector<char>& initial_bytes)
{
    *buf = initial_bytes;
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t
CPPY_IO_BytesIO_read(std::vector<char>* buf, size_t* pos, std::vector<char>* const result, size_t size)
{
    if (*pos >= buf->size())
        return CPPY_ERROR_t::EOFError;

    size_t available = buf->size() - *pos;
    if (size == static_cast<size_t>(-1) || size > available)
        size = available;

    result->assign(buf->begin() + static_cast<ptrdiff_t>(*pos),
                   buf->begin() + static_cast<ptrdiff_t>(*pos + size));
    *pos += size;
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t
CPPY_IO_BytesIO_write(std::vector<char>* buf, size_t* pos, const std::vector<char>& data)
{
    if (*pos + data.size() > buf->size())
    {
        buf->resize(*pos + data.size());
    }
    std::copy(data.begin(), data.end(), buf->begin() + static_cast<ptrdiff_t>(*pos));
    *pos += data.size();
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_BytesIO_getvalue(std::vector<char>* buf, std::vector<char>* const result)
{
    *result = *buf;
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_BytesIO_seek(std::vector<char>* buf, size_t* pos, long offset, int whence)
{
    size_t new_pos;
    switch (whence)
    {
    case 0: // SEEK_SET
        new_pos = static_cast<size_t>(offset);
        break;
    case 1: // SEEK_CUR
        if (offset < 0 && static_cast<size_t>(-offset) > *pos)
            return CPPY_ERROR_t::ValueError;
        new_pos = static_cast<size_t>(static_cast<long>(*pos) + offset);
        break;
    case 2: // SEEK_END
        if (offset < 0 && static_cast<size_t>(-offset) > buf->size())
            return CPPY_ERROR_t::ValueError;
        new_pos = static_cast<size_t>(static_cast<long>(buf->size()) + offset);
        break;
    default:
        return CPPY_ERROR_t::ValueError;
    }
    *pos = new_pos;
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_BytesIO_tell(std::vector<char>* /*buf*/, size_t* pos, long* const result)
{
    *result = static_cast<long>(*pos);
    return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_BytesIO_truncate(std::vector<char>* buf, size_t* pos, long size)
{
    if (size == -1)
        size = static_cast<long>(*pos);
    if (size < 0)
        size = 0;
    if (static_cast<size_t>(size) < buf->size())
    {
        buf->resize(static_cast<size_t>(size));
    }
    if (*pos > static_cast<size_t>(size))
        *pos = static_cast<size_t>(size);
    return CPPY_ERROR_t::Ok;
}
