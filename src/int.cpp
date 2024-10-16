#include <stdexcept>

#include "cppy/int.h"


CPPY_API PyException CPPY_INT_init(const std::string& str, int* const result) {
	try
	{
		*result = std::stoi(str);
	}
	catch (const std::invalid_argument&)
	{
		return PyException::ValueError;
	}
	catch (const std::out_of_range&)
	{
		return PyException::ValueError;
	}
	return PyException::Ok;
}

