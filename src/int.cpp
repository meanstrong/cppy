#include <stdexcept>
#include <bit>

#include "cppy/int.h"


CPPY_API PyException CPPY_INT_init(const std::string& str, int* const result) {
	return CPPY_INT_init(str, 10, result);
}

CPPY_API PyException CPPY_INT_init(const std::string& str, int base, int* const result) {
	try
	{
		*result = std::stoi(str, nullptr, base);
	}
	catch (const std::invalid_argument&)
	{
		return PyException::ValueError;
	}
	catch (const std::out_of_range&)
	{
		return PyException::OverflowError;
	}
	return PyException::Ok;
}

CPPY_API PyException CPPY_INT_bit_length(int x, int* const result) {
	if (x < 0) x = -x;
	*result = 0;

	if (x >= 0x10000)
	{
		*result += 16;
		x >>= 16;
	}
	if (x >= 0x100)
	{
		*result += 8;
		x >>= 8;
	}
	if (x >= 0x10)
	{
		*result += 4;
		x >>= 4;
	}
	if (x >= 0x4)
	{
		*result += 2;
		x >>= 2;
	}
	*result += x;
	return PyException::Ok;
}

CPPY_API PyException CPPY_INT_bit_count(int x, int* const result) {
	if (x < 0) x = -x;
	*result = 0;

	int i;
	for (i = 1; i <= x; i = i << 1)
		if (x & i)
			++(*result);

	return PyException::Ok;
}

