#include "Settings.h"
#include "Events/Events.h"
#include "States/Id.h"
#include <iostream>

namespace Settings
{
	std::string playerControlUp = "Up Arrow";
	std::string playerControlDown = "Down Arrow";
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

}

