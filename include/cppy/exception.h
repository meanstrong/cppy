#pragma once

#include <iostream>
#include <sstream>
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
	MemoryError,
	NotImplementedError,
};

class CPPY_Assertion_message
{
public:
	using message_type = std::stringstream;

	typedef std::ostream& (*BasicNarrowIoManip)(std::ostream&);

	CPPY_Assertion_message() : m_msg(new message_type) {};

	CPPY_Assertion_message(const CPPY_Assertion_message& msg) : m_msg(new message_type) {
		*m_msg << msg.GetString();
	}

	std::string GetString() const { return m_msg->str(); };

	template <typename T>
	CPPY_Assertion_message& operator<<(const T& value) {
		*m_msg << value;
		return *this;
	};

	CPPY_Assertion_message& operator<<(const char* value) {
		*m_msg << value;
		return *this;
	};

	CPPY_Assertion_message& operator<<(BasicNarrowIoManip val) {
		*m_msg << val;
		return *this;
	}

private:
	const std::unique_ptr<message_type> m_msg;
};

class CPPY_Expect_result
{
public:

	CPPY_Expect_result() {};

	void operator=(const CPPY_Assertion_message& result) const { std::cout << result.GetString() << std::endl; };
};

class CPPY_Assertion_result
{
public:

	CPPY_Assertion_result() {};

	void operator=(const CPPY_Assertion_message& result) const {
		std::cout << result.GetString() << std::endl;
		throw result;
	};
};

#define CPPY_EXPECT(v) \
    if (v)             \
        ;              \
    else               \
        CPPY_Expect_result() = CPPY_Assertion_message() << "ExpectFailure: " << __FILE__ << ":" << __LINE__ << std::endl

#define CPPY_ASSERT(v) \
    if (v)        \
        ;         \
    else          \
        CPPY_Assertion_result() = CPPY_Assertion_message() << "AssertionError: " << __FILE__ << ":" << __LINE__ << std::endl
