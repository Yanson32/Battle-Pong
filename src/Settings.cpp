#include "Settings.h"


WindowSettings::WindowSettings(): vMode(800, 600)
{

}


sf::VideoMode WindowSettings::getVideoMode() const
{
    return vMode;
}


WindowSettings::~WindowSettings()
{

}


Settings::Settings()
{
	title = "Pong";
}

sf::String Settings::getTitle() const
{
	return title;
}

Settings::~Settings()
{
}


Settings& Settings::inst()
{
	static Settings settings;
	return settings;
}

WindowSettings Settings::getWindowSettings() const
{
    return windowSettings;
}
