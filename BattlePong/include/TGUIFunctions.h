#ifndef TGUIFUNCTIONS_H
#define TGUIFUNCTIONS_H
#include <SFML/System/String.hpp>
#include <TGUI/TGUI.hpp>
#include <string>

tgui::String toTguiString(const int &num);
tgui::String toTguiString(const std::string &msg);


#endif 
