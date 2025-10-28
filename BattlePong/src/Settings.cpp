#include "Settings.h"
#include "Events/Events.h"
#include "Engin/States/StateId.h"
#include <iostream>
#include <SFML/System/String.hpp>
#include <GameUtilities/Log/LogType.h>
#define TO_STR2(x) #x
#define TO_STR(x) TO_STR2(x)

namespace Settings
{
    //Game settings
    sf::String ai = "Medium";
    int wallThickness = 25;
    int paddleThickness = 25;
    int paddleOffset= 25;
    StateId stateId = StateId::INTRO_STATE;
    int ballRadius = 5;  
    int ballSpeed = 3;
    int paddleSpeed = 200;
    std::string logFile = "log.txt";
    sf::Color textColor = sf::Color::Red;
    int collisionTime = 15;
    std::string leftPaddleTitle = "Left";
    std::string rightPaddleTitle = "Right";
    std::string connectIp = "";

    //Paddle 1 settings
    std::string p1Name = "";
    int p1Score = 0;

    //Paddle 2 settings
    std::string p2Name = "";
    int p2Score = 0;


    //Player controls
    std::string keyboardControlUp = "Up Arrow";
    std::string keyboardControlDown = "Down Arrow";
    std::string keyboardControlLeft = "Left Arrow";
    std::string keyboardControlRight = "Right Arrow";
    std::string keyboardControlMenu = "Escape";
    std::string keyboardControlNext = "Tab";
    std::string keyboardControlSelect = "Enter";
    std::string keyboardControlPause = "P";

    //Joystick buttons
    std::string joystickControlMenu;
    std::string joystickControlNext;
    std::string joystickControlSelect;
    //sf::Vector2f wDimensions = sf::Vector2f(800, 600);

    //music settings
    int musicVolume = 100;
    int soundVolume = 100;
    int currentSong = 0;
    std::vector<std::string> songList = {"Zombies", "Dreams"};


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
    int port = 4000;
    TS_String publicIp;
    std::string localIp = sf::IpAddress::getLocalAddress().toString();
    std::string clientIp = "";

    std::string preferencesFile = "";

    //Directories
    const std::string GAME_CONFIG_DIR = TO_STR(BP_GAME_CONFIG_DIR);
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


    //Credits
    int creditsTime = 5;

    bool isHost = false;
    bool isClient = false;
    bool multiplayer = false;

    sf::Color leftPaddleColor = sf::Color::Red;
    sf::Color rightPaddleColor = sf::Color::Blue;
    
    bool systemPaused = false;
    bool playerPaused = false;
    bool clientPaused = false;
}
