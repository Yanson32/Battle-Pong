
#include "Settings.h"
#include "Events/Events.h"
#include "States/StateId.h"
#include <iostream>
#include <SFML/System/String.hpp>

namespace Settings
{
    //Game settings
    sf::String time = "30";
    sf::String ai = "Medium"; 
    const float wallThickness = 25;
    StateId stateId = StateId::INTRO_STATE;
    
    //Paddle 1 settings
    std::string p1Input = "";
    std::string p1Name = "";
    int p1Score = 0;
    
    //Paddle 2 settings
    std::string p2Input = "";
    std::string p2Name = "";
    int p2Score = 0;


    //Player controls
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
	
    //music settings 
    int mVolume = 100;
    int sVolume = 100;
    sf::String currentSong = "zombies";
	
   
    std::string input  = "Medium";
    std::string playerName = "Player 1";
    int score = 0;

    //Button settings
    sf::Vector2f bSize = sf::Vector2f(200, 25);
    sf::Vector2f bPosition = sf::Vector2f(300, 300);


    //Window settings    
    sf::String title = "Battle Pong";
    sf::Vector2f dimensions = sf::Vector2f(1280, 720);
	
    
    //Theme
    std::string theme = "Black";
    std::string background = "Star";

    //Network 
    sf::TcpSocket socket;
    sf::TcpListener listener;
    bool connected = false;
    int port = 4000;
    sf::String targetIp = "127.0.0.0";
    sf::Time timeOut;
    std::string publicIp = "0.0.0.0"; 
    std::string localIp = sf::IpAddress::getLocalAddress().toString();
    
    

    //Directories
    const std::string RESOURCE_INSTALL_DIR = RESOURCE_INSTALL_PATH;
    const std::string RESOURCE_BINARY_DIR = RESOURCE_BINARY_PATH;
    const std::string IMAGES_INSTALL_DIR = RESOURCE_INSTALL_DIR + "/Images/";
    const std::string IMAGES_BINARY_DIR = RESOURCE_BINARY_DIR + "/Images/";
    const std::string SOUNDS_INSTALL_DIR = RESOURCE_INSTALL_DIR + "/Sounds/";
    const std::string SOUNDS_BINARY_DIR = RESOURCE_BINARY_DIR + "/Sounds/";
    const std::string FONTS_INSTALL_DIR = RESOURCE_INSTALL_DIR + "/Fonts/";
    const std::string FONTS_BINARY_DIR = RESOURCE_BINARY_DIR + "/Fonts/";
    const std::string THEME_INSTALL_DIR = RESOURCE_INSTALL_DIR + "/TGUI/Theme/";
    const std::string THEME_BINARY_DIR = RESOURCE_BINARY_DIR + "/TGUI/Theme/";
    const std::string MUSIC_INSTALL_DIR = RESOURCE_INSTALL_DIR + "/Music/";
    const std::string MUSIC_BINARY_DIR = RESOURCE_BINARY_DIR + "/Music/";
    const std::string BACKGROUNDS_INSTALL_DIR = RESOURCE_INSTALL_DIR + "/Backgrounds/";
    const std::string BACKGROUNDS_BINARY_DIR = RESOURCE_BINARY_DIR + "/Backgrounds/";
}
