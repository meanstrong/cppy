#ifndef CPPY_IO_H
#define CPPY_IO_H

#include "cppy/internal/declare.h"
#include "cppy/exception.h"
#include "cppy/str.h"

template <typename IOStream>
CPPY_API CPPY_ERROR_t CPPY_IO_open(const std::string& file, IOStream* const iostream, const std::string& mode = "r") {
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
	return CPPY_ERROR_t::Ok;
};

template <typename IOStream>
CPPY_API CPPY_ERROR_t CPPY_IO_readline(IOStream& iostream, std::string* const s) {
	if (std::getline(iostream, *s))
		return CPPY_ERROR_t::Ok;
	return CPPY_ERROR_t::EOFError;
};

template <typename IOStream>
CPPY_API CPPY_ERROR_t CPPY_IO_write(IOStream& iostream, const std::string& s) {
	iostream.write(s.c_str(), s.size());
	return CPPY_ERROR_t::Ok;
};

template <typename IOStream>
CPPY_API CPPY_ERROR_t CPPY_IO_close(IOStream& iostream) {
	iostream.close();
	return CPPY_ERROR_t::Ok;
};

#endif // CPPY_IO_H
