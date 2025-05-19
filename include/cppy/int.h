#pragma once

#include <string>

#include "cppy/internal/declare.h"
#include "cppy/exception.h"

/* int(str, base=10) -> integer
*
*  Convert a string to an integer
*
*  The literal can be preceded by '+' or '-' and be surrounded
*  by whitespace.  The base defaults to 10.  Valid bases are 0 and 2-36.
*  Base 0 means to interpret the base from the string as an integer literal.
*/
CPPY_API CPPY_ERROR_t CPPY_INT_init(int* const x, const std::string& str, int base=10);

/* Number of bits necessary to represent self in binary.
*
*  >>> bin(37)
*  '0b100101'
*  >>> (37).bit_length()
*  6
*/
CPPY_API CPPY_ERROR_t CPPY_INT_bit_length(int x, int* const result);

/* Number of ones in the binary representation of the absolute value of self.
*
*  Also known as the population count.
*
*  >>> bin(13)
*  '0b1101'
*  >>> (13).bit_count()
*  3
*/
CPPY_API CPPY_ERROR_t CPPY_INT_bit_count(int x, int* const result);
