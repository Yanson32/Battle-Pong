#include "Settings.h"
#include "Events/Events.h"
#include "States/Id.h"
#include <iostream>

namespace tempSettings
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
}

ClientSettings::ClientSettings()
{
    //ctor
    setTimeOut(sf::seconds(5));
}

bool ClientSettings::isConnected()
{

}

void ClientSettings::init()
{

    sf::Socket::Status status = socket.connect({ip}, port, sf::seconds(5));
    if (status != sf::Socket::Done)
    {
        // error...
        EventManager::inst().Post<GU::Evt::ChangeState>(stateId::CONNECT_STATE);
    }

}

void ClientSettings::clean()
{

}

void ClientSettings::handleEvents()
{

}

bool ClientSettings::update()
{

}

void ClientSettings::setTimeOut(const sf::Time &newTime)
{
    timeOut = newTime;
}


void ClientSettings::setIp(const sf::String newIp)
{
    ip = newIp;
}

void ClientSettings::setPort(const int newPort)
{
    port = newPort;
}

sf::String ClientSettings::getIp() const
{
    return ip;
}

int ClientSettings::getPort() const
{
    return port;
}

ClientSettings::~ClientSettings()
{
    //dtor
}


/**********************************************************//**
*   @brief  A singleton that contains all game settings
**************************************************************/
Settings::Settings():
bSize(200, 25),
bPosition(300, 300),
clientSettings(new ClientSettings()),
screen(800, 600)
{
	title = "Pong";
}

sf::String Settings::getTitle() const
{
	return title;
}

Settings::~Settings()
{
}


Settings& Settings::inst()
{
	static Settings settings;
	return settings;
}

sf::Vector2f Settings::buttonSize() const
{
    return bSize;
}

sf::Vector2f Settings::buttonPosition(const unsigned pos) const
{

    sf::Vector2f temp = bPosition;
    temp.y += 50 * pos;

    return temp;
}

