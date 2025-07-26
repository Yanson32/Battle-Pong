#include "TS_String.h"

TS_String::TS_String()
{

}

void TS_String::setString(const std::string string)
{
    std::lock_guard<std::mutex> lock(mutex);
    m_string = string;
}

std::string TS_String::getString()
{
    std::lock_guard<std::mutex> lock(mutex);
    return m_string;
}

TS_String::~TS_String()
{

}
