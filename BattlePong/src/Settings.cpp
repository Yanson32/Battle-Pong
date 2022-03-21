#include "Settings.h"
#include "Events/Events.h"
#include "States/StateId.h"
#include <iostream>

namespace Settings
{
	std::string playerControlUp = "Up Arrow";
	std::string playerControlDown = "Down Arrow";
	std::string playerControlLeft = "Left Arrow";
	std::string playerControlRight = "Right Arrow";
	std::string playerControlMenu = "Escape";
	std::string playerControlNext = "Tab";
	std::string playerControlSelect = "Enter";

    //Joystick buttons    
	std::string playerJoystickControlNext;  
	std::string playerJoystickControlSelect;  
    sf::Vector2f wDimensions = sf::Vector2f(800, 600);
	
	PaddleSettings paddle1;
	PaddleSettings paddle2;
	MusicSettings music;
	std::string input  = "Medium";
	std::string playerName = "Player 1";
	int score = 0;

	//Server Settings
	ServerSettings server;

	//Client Settings
	ClientSettings client;

	//Ball
	ButtonSettings button;
	
	//Window
	WindowSettings window; 
    
    //Game settings
    GameSettings game;
    
	const float wallThickness = 25;
    std::string theme = "Black";

    std::string publicIp = "0.0.0.0"; 
    std::string localIp = sf::IpAddress::getLocalAddress().toString();
    std::string port = "5000";
    std::string background = "Star";
    StateId stateId = StateId::INTRO_STATE;

    //Directories
    const std::string RESOURCE_DIR = "../Resources";
    const std::string IMAGES_DIR = RESOURCE_DIR + "/Images";
    const std::string SOUNDS_DIR = RESOURCE_DIR + "/Sounds";
    const std::string FONTS_DIR = RESOURCE_DIR + "/Fonts";
    const std::string THEME_DIR = RESOURCE_DIR + "/TGUI/Theme";
    const std::string MUSIC_DIR = RESOURCE_DIR + "/Music";
    const std::string BACKGROUNDS_DIR = RESOURCE_DIR + "Backgrounds";
}

