#include "SFMLFunctions.h"
#include <string>
#include <iostream>

int toInt(const sf::String num)
{
    std::string temp = num.toAnsiString();

    return std::atoi(num.toAnsiString().c_str());
}
