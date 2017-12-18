#ifndef SETTINGS_H
#define SETTINGS_H
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>

class WindowSettings
{
    public:
        WindowSettings();
        sf::VideoMode getVideoMode() const;
        ~WindowSettings();
    private:
        sf::VideoMode vMode;

};

class Settings
{
public:
	sf::String getTitle() const;
	static Settings& inst();
	WindowSettings getWindowSettings() const;
	~Settings();
private:
	sf::String title;
	Settings();
	Settings operator = (const Settings settings) = delete;
	Settings(const Settings &settings) = delete;
	WindowSettings windowSettings;
};


#endif
