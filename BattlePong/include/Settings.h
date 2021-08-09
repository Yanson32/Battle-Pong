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

namespace Settings 
{
    struct GameSettings
    {
        sf::String time = "30";
        sf::String ai = "Medium"; 
    };

	struct PaddleSettings
	{
		std::string input;
		std::string name;
		int score;
	};
    
    struct MusicSettings
	{
        int mVolume = 100;
    	int sVolume = 100;
        sf::String currentSong = "Zombies";
    };
	
    struct ServerSettings
	{
        	sf::TcpSocket socket;
        	sf::TcpListener listener;
        	bool connected = false;
        	int port = 4000;
        	sf::IpAddress address;

	};

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
		sf::String title = "Test";
		sf::Vector2f dimensions = sf::Vector2f(1280, 720);
	};
    extern std::string theme;
	extern std::string playerControlUp;
	extern std::string playerControlDown;
	

	extern PaddleSettings paddle1;
	extern PaddleSettings paddle2;
	extern MusicSettings music;
	
	//Server
	extern ServerSettings server;

	//Client
	extern ClientSettings client;

	//Ball
	extern	ButtonSettings button;

	//Window
	extern WindowSettings window;

    //Game settings
    extern GameSettings game;

	extern const float wallThickness;

    extern const std::string globalIp;
    extern const std::string localIp;
    extern const std::string port;
    extern std::string background;
}


#endif
