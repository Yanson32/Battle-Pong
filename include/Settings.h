#ifndef SETTINGS_H
#define SETTINGS_H
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <TGUI/TGUI.hpp>

class WindowSettings
{
    public:
        WindowSettings();
        sf::VideoMode getVideoMode() const;
        ~WindowSettings();
    private:
        sf::VideoMode vMode;

};

class PaddleSettings: public tgui::Panel
{
    public:
        PaddleSettings(const sf::String &newName);
        sf::String getPlayerName() const;
        sf::String getInputType() const;
        ~PaddleSettings();
    private:
        sf::String name;
        sf::String playerName;
        sf::String cBoxItem;
        tgui::EditBox::Ptr eBox;
        tgui::ComboBox::Ptr cBox;
        void onNameBox();
        void onListItemSelected();
};

class Settings
{
public:
	sf::String getTitle() const;
	static Settings& inst();
	WindowSettings getWindowSettings() const;
	sf::Vector2f buttonSize() const;
	sf::Vector2f buttonPosition(const unsigned pos = 0) const;
    std::shared_ptr<PaddleSettings> paddle1;
	std::shared_ptr<PaddleSettings> paddle2;
	WindowSettings windowSettings;
	~Settings();
private:
	sf::String title;
	Settings();
	Settings operator = (const Settings settings) = delete;
	Settings(const Settings &settings) = delete;

	sf::Vector2f bSize;
	sf::Vector2f bPosition;
};


#endif
