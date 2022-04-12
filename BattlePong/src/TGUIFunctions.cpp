#include "TGUIFunctions.h"
#include <cstdint>

tgui::String toTguiString(const int &num)
{
	return sf::String(std::to_string(num)).toAnsiString();
}

tgui::String toTguiString(const std::string &msg)
{
	tgui::String temp(msg);
	return temp.toAnsiString();
}
