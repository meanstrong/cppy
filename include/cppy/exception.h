#ifndef CPPY_EXCEPTION_H
#define CPPY_EXCEPTION_H

#include <iostream>
#include <string>

#include "cppy/internal/declare.h"

enum class CPPY_ERROR_t : unsigned int
{
	Ok = 0,
	ValueError = 1,
	IndexError = 2,
	OverflowError = 3,
	KeyError = 4,
	EOFError,
	NotImplementedError,
};

class CPPY_Assertion_message
{
public:
	CPPY_Assertion_message() {};

	const char* message() const { return m_msg.c_str(); };

	CPPY_Assertion_message& operator<<(const std::string& value) {
		m_msg += value;
		return *this;
	};

	CPPY_Assertion_message& operator<<(const char* value) {
		m_msg += value;
		return *this;
	};

	template<typename T>
	CPPY_Assertion_message& operator<<(const T& value) {
		m_msg += std::to_string(value);
		return *this;
	};

private:
	std::string m_msg;
};

class CPPY_Expect_result
{
public:

	CPPY_Expect_result() {};

	void operator=(const CPPY_Assertion_message& result) const { std::cout << result.message() << std::endl; };
};

class CPPY_Assertion_result
{
public:

	CPPY_Assertion_result() {};

	void operator=(const CPPY_Assertion_message& result) const {
		std::cout << result.message() << std::endl;
		throw result;
	};
};

#define CPPY_EXPECT(v) \
    if (v)             \
        ;              \
    else               \
        CPPY_Expect_result() = CPPY_Assertion_message() << "ExpectFailure: " << #v << " " << __FILE__ << ":" << __LINE__ << ". "

#define CPPY_ASSERT(v) \
    if (v)        \
        ;         \
    else          \
        CPPY_Assertion_result() = CPPY_Assertion_message() << "AssertionError: " << #v << " " << __FILE__ << ":" << __LINE__ << ". "

#endif // CPPY_EXCEPTION_H
