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
#include <SFML/Network.hpp>
#include "Events/EventId.h"
#include "States/StateId.h"
#include <string>

namespace Settings 
{
    //Game settings
    extern sf::String time;
    extern sf::String ai;

    //Paddle 1 settigns
    extern std::string p1Input;
    extern std::string p1Name;
    extern int p1Score;
    
    //Paddle 2 settigns
    extern std::string p2Input;
    extern std::string p2Name;
    extern int p2Score;
    
    
    struct MusicSettings
	{
        int mVolume = 100;
    	int sVolume = 100;
        sf::String currentSong = "Zombies";
    };
	//Server	
       extern sf::TcpSocket socket;
       extern sf::TcpListener listener;
       extern bool connected;
       extern int port;
       extern sf::IpAddress address;


	struct ClientSettings 
	{
        	int port = 5000;
        	sf::String ip = "127.0.0.0.1";
        	sf::TcpSocket socket;
        	sf::Time timeOut;
	};
	
	struct ButtonSettings
	{	
		sf::Vector2f bSize = sf::Vector2f(200, 25);
		sf::Vector2f bPosition = sf::Vector2f(300, 300);
	};
	    
	struct WindowSettings
	{
		sf::String title = "Battle Pong";
		sf::Vector2f dimensions = sf::Vector2f(1280, 720);
	};
    extern std::string theme;
	extern std::string playerControlUp;
	extern std::string playerControlDown;
	extern std::string playerControlLeft;
	extern std::string playerControlRight;
	extern std::string playerControlMenu;
	extern std::string playerControlNext;
	extern std::string playerControlSelect;

    //Joystick buttons    
	extern std::string playerJoystickControlNext;
	extern std::string playerJoystickControlSelect;  

	extern MusicSettings music;
	
	//Client
	extern ClientSettings client;

	//Ball
	extern	ButtonSettings button;

	//Window
	extern WindowSettings window;


	extern const float wallThickness;

    extern std::string publicIp;
    extern std::string localIp;
    extern std::string background;

    extern StateId stateId;



    extern const std::string RESOURCE_DIR; 
    extern const std::string IMAGES_DIR;
    extern const std::string SOUNDS_DIR;
    extern const std::string FONTS_DIR;
    extern const std::string THEME_DIR;
    extern const std::string MUSIC_DIR;
    extern const std::string BACKGROUNDS_DIR; 
}


#endif
