#include "cppy/exception.h"

CPPY_Assertion_message::CPPY_Assertion_message() : m_msg(new message_type){}

CPPY_Assertion_message::CPPY_Assertion_message(const CPPY_Assertion_message& msg) : m_msg(new message_type)
{
    *m_msg << msg.GetString();
}

std::string CPPY_Assertion_message::GetString() const
{
    return m_msg->str();
}

CPPY_Assertion_message& CPPY_Assertion_message::operator<<(const char* value)
{
    *m_msg << value;
    return *this;
}

CPPY_Assertion_message& CPPY_Assertion_message::operator<<(BasicNarrowIoManip val)
{
    *m_msg << val;
    return *this;
}

CPPY_Expect_result::CPPY_Expect_result(){};

void CPPY_Expect_result::operator=(const CPPY_Assertion_message& result) const
{
    std::cout << result.GetString() << std::endl;
}

CPPY_Assertion_result::CPPY_Assertion_result(){}

void CPPY_Assertion_result::operator=(const CPPY_Assertion_message& result) const
{
    std::cout << result.GetString() << std::endl;
    throw result;
}
