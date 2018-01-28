#ifndef SETTINGS_H
#define SETTINGS_H
/**********************************************************//**
*   @author Wayne J Larson Jr.
*   @date   12/25/17
*   @brief  The MusicSettings constructor
**************************************************************/

#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <TGUI/TGUI.hpp>

#include "Events/Id.h"

/**********************************************************//**
*   @brief  Settings for the game window
**************************************************************/
class WindowSettings
{
    public:
        WindowSettings();
        sf::VideoMode getVideoMode() const;
        ~WindowSettings();
    private:
        sf::VideoMode vMode;

};


/**********************************************************//**
*   @brief  Settings for a single paddle
**************************************************************/
class PaddleSettings: public tgui::Panel
{
    public:
        PaddleSettings(const sf::String &newName, ObjectId newId);
        sf::String getPlayerName() const;
        void setPlayerName(const sf::String &newName);
        sf::String getInputType() const;
        void setInputType(const sf::String &newInput);
        int getScore() const;
        void setScore(const int newScore);
        ObjectId getId() const;
        ~PaddleSettings();
    private:
        //sf::String name;
        sf::String input;
        sf::String playerName;
        sf::String cBoxItem;
        tgui::EditBox::Ptr eBox;
        tgui::ComboBox::Ptr cBox;
        int score = 0;
        ObjectId paddleId;
        //void onNameBox();
        //void onListItemSelected();
};


/**********************************************************//**
*   @brief  Settings for music
**************************************************************/
class MusicSettings: public tgui::Panel
{
    public:
        MusicSettings();
        int getVolume() const;
        int getSoundVolume() const;
    private:
        tgui::Slider::Ptr musicVolume;
        tgui::Slider::Ptr soundVolume;
        int mVolume = 200;
        int sVolume = 150;
        void onMusicVolume();
        void onSoundVolume();

};


/**********************************************************//**
*   @brief  A singleton that contains all game settings
**************************************************************/
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
	std::shared_ptr<MusicSettings> musicSettings;
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
