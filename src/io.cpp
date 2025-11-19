#pragma once

#include "cppy/io.h"

CPPY_IO_IOBase::CPPY_IO_IOBase() : _closed(false) {}

bool CPPY_IO_IOBase::closed() const { return _closed; }

void CPPY_IO_IOBase::close() { _closed = true; }

void CPPY_IO_IOBase::flush() {}

void CPPY_IO_IOBase::_check_closed() const {
	CPPY_ASSERT(!_closed) << "ValueError: I/O operation on closed file.";
}

CPPY_IO_StringIO::CPPY_IO_StringIO(const std::string& initial_value,
	bool readable, bool writable)
	: _readable(readable), _writable(writable) {
	if (writable) {
		_stream << initial_value;
	}
	else if (readable) {
		_stream.str(initial_value);
	}
}

void CPPY_IO_StringIO::flush() {
	_stream.flush();
}

bool CPPY_IO_StringIO::readable() {
	return _readable;
}

bool CPPY_IO_StringIO::writable() {
	return _writable;
}

CPPY_ERROR_t CPPY_IO_StringIO::read(std::string* const result, size_t size) {
	_check_closed();
	CPPY_ASSERT(readable()) << "io.UnsupportedOperation: not readable";

	if (size == static_cast<size_t>(-1)) {
		*result = _stream.str().substr(_stream.tellg());
		_stream.seekg(0, std::ios::end);
	}
	else {
		result->resize(size);
		if (!_stream.read(&result->front(), size))
			return CPPY_ERROR_t::EOFError;
		result->resize(_stream.gcount());
	}
	return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_StringIO::readline(std::string* const result,
	size_t size) {
	_check_closed();
	CPPY_ASSERT(readable()) << "io.UnsupportedOperation: not readable";

	if (size == static_cast<size_t>(-1)) {
		if (!std::getline(_stream, *result))
			return CPPY_ERROR_t::EOFError;
	}
	else {
		result->resize(size);
		if (!_stream.getline(&result->front(), size))
			return CPPY_ERROR_t::EOFError;
		result->resize(_stream.gcount());
	}
	return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t
CPPY_IO_StringIO::readlines(std::vector<std::string>* const result) {
	_check_closed();
	CPPY_ASSERT(readable()) << "io.UnsupportedOperation: not readable";

	std::string line;
	while (std::getline(_stream, line)) {
		result->push_back(line);
	}
	return CPPY_ERROR_t::Ok;
}

void CPPY_IO_StringIO::write(const std::string& s) {
	_check_closed();
	CPPY_ASSERT(writable()) << "io.UnsupportedOperation: not writable";

	_stream << s;
}

void CPPY_IO_StringIO::writelines(const std::vector<std::string>& lines) {
	_check_closed();
	CPPY_ASSERT(writable()) << "io.UnsupportedOperation: not writable";

	for (const auto& line : lines) {
		_stream << line;
	}
}

std::string CPPY_IO_StringIO::getvalue() const { return _stream.str(); }

CPPY_IO_FileIO::CPPY_IO_FileIO(const std::string& filename,
	const std::string& mode)
	: _mode(mode) {
	std::ios_base::openmode open_mode = 0;

	if (mode.find('r') != std::string::npos) {
		open_mode |= std::ios_base::in;
	}
	if (mode.find('w') != std::string::npos) {
		open_mode |= std::ios_base::out | std::ios_base::trunc;
	}
	if (mode.find('a') != std::string::npos) {
		open_mode |= std::ios_base::out | std::ios_base::app;
	}
	if (mode.find('+') != std::string::npos) {
		open_mode |= std::ios_base::in | std::ios_base::out;
	}
	if (mode.find('b') != std::string::npos) {
		open_mode |= std::ios_base::binary;
	}

	_file.open(filename, open_mode);
	CPPY_ASSERT(_file.is_open()) << "FileNotFoundError: No such file or directory: '" << filename << "'";
}

CPPY_IO_FileIO::~CPPY_IO_FileIO() {
	if (_file.is_open()) {
		_file.close();
	}
}

void CPPY_IO_FileIO::close() {
	_check_closed();
	_file.close();
	CPPY_IO_IOBase::close();
}

void CPPY_IO_FileIO::flush() {
	_file.flush();
}

bool CPPY_IO_FileIO::readable() {
	return !(_mode.find('r') == std::string::npos &&
		_mode.find('+') == std::string::npos);
}

bool CPPY_IO_FileIO::writable() {
	return !(_mode.find('w') == std::string::npos &&
		_mode.find('a') == std::string::npos &&
		_mode.find('+') == std::string::npos);
}

CPPY_ERROR_t CPPY_IO_FileIO::read(std::string* const result, size_t size) {
	_check_closed();
	CPPY_ASSERT(readable()) << "io.UnsupportedOperation: not readable";

	if (size == static_cast<size_t>(-1)) {
		*result = std::string(std::istreambuf_iterator<char>(_file), {});
	}
	else {
		result->resize(size);
		if (!_file.read(&result->front(), size))
			return CPPY_ERROR_t::EOFError;
		result->resize(_file.gcount());
	}
	return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_FileIO::readline(std::string* const result, size_t size) {
	_check_closed();
	CPPY_ASSERT(readable()) << "io.UnsupportedOperation: not readable";

	if (size == static_cast<size_t>(-1)) {
		if (!std::getline(_file, *result))
			return CPPY_ERROR_t::EOFError;
	}
	else {
		result->resize(size);
		if (!_file.getline(&result->front(), size))
			return CPPY_ERROR_t::EOFError;
		result->resize(_file.gcount());
	}
	return CPPY_ERROR_t::Ok;
}

CPPY_ERROR_t CPPY_IO_FileIO::readlines(std::vector<std::string>* const result) {
	_check_closed();
	CPPY_ASSERT(readable()) << "io.UnsupportedOperation: not readable";

	std::string line;
	while (std::getline(_file, line)) {
		result->push_back(line);
	}
	return CPPY_ERROR_t::Ok;
}

void CPPY_IO_FileIO::write(const std::string& s) {
	_check_closed();
	CPPY_ASSERT(writable()) << "io.UnsupportedOperation: not writable";

	_file << s;
}

void CPPY_IO_FileIO::writelines(const std::vector<std::string>& lines) {
	_check_closed();
	CPPY_ASSERT(writable()) << "io.UnsupportedOperation: not writable";

	for (const auto& line : lines) {
		_file << line;
	}
}

CPPY_IO_BytesIO::CPPY_IO_BytesIO(const std::vector<char>& initial_bytes,
	bool readable, bool writable)
	: _buffer(initial_bytes), _position(0), _readable(readable),
	_writable(writable) {
}

bool CPPY_IO_BytesIO::readable() {
	return _readable;
}

bool CPPY_IO_BytesIO::writable() {
	return _writable;
}

CPPY_ERROR_t CPPY_IO_BytesIO::read(std::vector<char>* const result,
	size_t size) {
	_check_closed();
	CPPY_ASSERT(readable()) << "io.UnsupportedOperation: not readable";

	if (size == static_cast<size_t>(-1) || _position + size > _buffer.size()) {
		size = _buffer.size() - _position;
	}

	result->insert(result->end(), _buffer.begin() + _position,
		_buffer.begin() + _position + size);
	_position += size;
	return CPPY_ERROR_t::Ok;
}

void CPPY_IO_BytesIO::write(const std::vector<char>& data) {
	_check_closed();
	CPPY_ASSERT(writable()) << "io.UnsupportedOperation: not writable";

	if (_position > _buffer.size()) {
		_buffer.resize(_position);
	}

	size_t space_needed = _position + data.size() - _buffer.size();
	if (space_needed > 0) {
		_buffer.resize(_buffer.size() + space_needed);
	}

	std::copy(data.begin(), data.end(), _buffer.begin() + _position);
	_position += data.size();
}

std::vector<char> CPPY_IO_BytesIO::getvalue() const { return _buffer; }
