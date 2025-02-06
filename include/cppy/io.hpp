#ifndef CPPY_IO_H
#define CPPY_IO_H

#include "cppy/internal/declare.h"
#include "cppy/exception.h"
#include "cppy/str.h"

template <typename IOStream>
CPPY_API PyException CPPY_IO_open(const std::string& file, IOStream* const iostream, const std::string& mode = "r") {
	std::ios_base::openmode openmode = 0;
	bool whether{ false };
	CPPY_STR_iscontain(mode, "r", &whether);
	if (whether)
		openmode |= std::ios_base::in;
	CPPY_STR_iscontain(mode, "w", &whether);
	if (whether)
		openmode |= std::ios_base::out;
	CPPY_STR_iscontain(mode, "a", &whether);
	if (whether)
		openmode |= std::ios_base::app;
	iostream->open(file, openmode);
	return PyException::Ok;
};

template <typename IOStream>
CPPY_API PyException CPPY_IO_readline(IOStream& iostream, std::string* const s) {
	if (std::getline(iostream, *s))
		return PyException::Ok;
	return PyException::EOFError;
};

template <typename IOStream>
CPPY_API PyException CPPY_IO_write(IOStream& iostream, const std::string& s) {
	iostream.write(s.c_str(), s.size());
	return PyException::Ok;
};

template <typename IOStream>
CPPY_API PyException CPPY_IO_close(IOStream& iostream) {
	iostream.close();
	return PyException::Ok;
};

#endif // CPPY_IO_H
