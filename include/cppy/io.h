#pragma once

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "cppy/exception.h"
#include "cppy/internal/declare.h"

/* The abstract base class for all I/O classes.
*
* This class provides dummy implementations for many methods that
* derived classes can override selectively; the default implementations
* represent a file that cannot be read, written or seeked.
*/
class CPPY_API CPPY_IO_IOBase {
protected:
	bool _closed;

public:
	CPPY_IO_IOBase();
	virtual ~CPPY_IO_IOBase() = default;

	virtual void close();
	virtual void flush();
	virtual bool readable() = 0;
	virtual bool writable() = 0;

	bool closed() const;

	void _check_closed() const;
};

/* Base class for text I/O.
*
* This class provides a character and line based interface to stream
* I/O. There is no readinto method because Python's character strings
* are immutable.
*/
class CPPY_API CPPY_IO_TextIOBase : public CPPY_IO_IOBase {
public:
	virtual CPPY_ERROR_t read(std::string* const result, size_t size = -1) = 0;
	virtual CPPY_ERROR_t readline(std::string* const result, size_t size = -1) = 0;
	virtual CPPY_ERROR_t readlines(std::vector<std::string>* const result) = 0;
	virtual void write(const std::string& s) = 0;
	virtual void writelines(const std::vector<std::string>& lines) = 0;
};

/* Text I/O implementation using an in-memory buffer.
*
* The initial_value argument sets the value of object.  The newline
* argument is like the one of TextIOWrapper's constructor.
*/
class CPPY_API CPPY_IO_StringIO : public CPPY_IO_TextIOBase {
private:
	std::stringstream _stream;
	bool _readable;
	bool _writable;

public:
	CPPY_IO_StringIO(const std::string& initial_value = "", bool readable = true,
		bool writable = true);

	void flush() override;

	bool readable() override;

	bool writable() override;

	CPPY_ERROR_t read(std::string* const result, size_t size = -1) override;

	CPPY_ERROR_t readline(std::string* const result, size_t size = -1) override;

	CPPY_ERROR_t readlines(std::vector<std::string>* const result) override;

	void write(const std::string& s) override;

	void writelines(const std::vector<std::string>& lines) override;

	std::string getvalue() const;
};

/* Open a file.
*
* The mode can be 'r' (default), 'w', 'x' or 'a' for reading,
* writing, exclusive creation or appending.  The file will be created if it
* doesn't exist when opened for writing or appending; it will be truncated
* when opened for writing.  A FileExistsError will be raised if it already
* exists when opened for creating. Opening a file for creating implies
* writing so this mode behaves in a similar way to 'w'.Add a '+' to the mode
* to allow simultaneous reading and writing. A custom opener can be used by
* passing a callable as *opener*. The underlying file descriptor for the file
* object is then obtained by calling opener with (*name*, *flags*).
* *opener* must return an open file descriptor (passing os.open as *opener*
* results in functionality similar to passing None).
*/
class CPPY_API CPPY_IO_FileIO : public CPPY_IO_TextIOBase {
private:
	std::fstream _file;
	std::string _mode;

public:
	CPPY_IO_FileIO(const std::string& filename, const std::string& mode = "r");

	~CPPY_IO_FileIO() override;

	void close() override;

	void flush() override;

	bool readable() override;

	bool writable() override;

	CPPY_ERROR_t read(std::string* const result, size_t size = -1) override;

	CPPY_ERROR_t readline(std::string* const result, size_t size = -1) override;

	CPPY_ERROR_t readlines(std::vector<std::string>* const result) override;

	void write(const std::string& s) override;

	void writelines(const std::vector<std::string>& lines) override;
};

/* Base class for buffered IO objects.
*
* The main difference with RawIOBase is that the read() method
* supports omitting the size argument, and does not have a default
* implementation that defers to readinto().
*
* In addition, read(), readinto() and write() may raise
* BlockingIOError if the underlying raw stream is in non-blocking
* mode and not ready; unlike their raw counterparts, they will never
* return None.
*
* A typical implementation should not inherit from a RawIOBase
* implementation, but wrap one.
*/
class CPPY_API CPPY_IO_BufferedIOBase : public CPPY_IO_IOBase {
public:
	virtual CPPY_ERROR_t read(std::vector<char>* const result, size_t size = -1) = 0;
	virtual void write(const std::vector<char>& data) = 0;
};

/* Buffered I/O implementation using an in-memory bytes buffer.
*/
class CPPY_API CPPY_IO_BytesIO : public CPPY_IO_BufferedIOBase {
private:
	std::vector<char> _buffer;
	size_t _position;
	bool _readable;
	bool _writable;

public:
	CPPY_IO_BytesIO(const std::vector<char>& initial_bytes = {}, bool readable = true,
		bool writable = true);

	bool readable() override;

	bool writable() override;

	CPPY_ERROR_t read(std::vector<char>* const result, size_t size = -1) override;

	void write(const std::vector<char>& data) override;

	std::vector<char> getvalue() const;
};
