#ifndef CPPY_EXCEPTION_H
#define CPPY_EXCEPTION_H


enum class PyException : unsigned int
{
	Ok = 0,
	ValueError = 1,
	IndexError = 2,
	OverflowError = 3,
};
#endif // CPPY_EXCEPTION_H
