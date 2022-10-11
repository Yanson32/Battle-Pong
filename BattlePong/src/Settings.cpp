
#include "Settings.h"
#include "Events/Events.h"
#include "States/StateId.h"
#include <iostream>
#include <SFML/System/String.hpp>
#include <GameUtilities/Log/LogType.h>

namespace Settings
{
    //Game settings
    sf::String time = "30";
    sf::String ai = "Medium";
    int wallThickness = 25;
    StateId stateId = StateId::INTRO_STATE;
    int ballRadius = 5;  
    int ballSpeed = 3;
    int paddleSpeed = 200;
    std::string logFile = "log.txt";

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
    std::string playerJoystickControlMenu;
    std::string playerJoystickControlNext;
    std::string playerJoystickControlSelect;
    sf::Vector2f wDimensions = sf::Vector2f(800, 600);

    //music settings
    int musicVolume = 100;
    int soundVolume = 100;
    int currentSong = 0;
    std::vector<std::string> songList = {"Zombies", "Dreams"};


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
    std::string currentBackground = "Star";
    std::vector<std::string> backgrounds = {"Star", "Nebula"};
    std::string currentTheme = "Black";
    std::vector<std::string> themes = {"Default", "Black", "BabyBlue"};

    //Network
    sf::TcpSocket socket;
    sf::TcpListener listener;
    bool connected = false;
    int port = 4000;
    sf::String targetIp = "127.0.0.0";
    sf::Time timeOut;
    std::string publicIp = "0.0.0.0";
    std::string localIp = sf::IpAddress::getLocalAddress().toString();

    std::string preferencesFile = "";

    //Directories
    const std::string RESOURCE_INSTALL_DIR = RESOURCE_INSTALL_PATH;

    int logSeverity = static_cast<int>(GU::Log::LogType::GU_MESSAGE);


    //Debug draw settings
    bool b2aabb = false;
    bool b2shapes = false;
    bool b2centerOfMass = false;
    bool b2joints = false;
    bool b2pair = false;
    
    int velocityIterations = 8;                   ///Box2D how strongly to correct velocity
    int positionIterations = 8;                   ///Box2D how strongly to correct position
    int frameRate = 60;
}
