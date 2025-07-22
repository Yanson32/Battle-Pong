#include "Network/Client.h"
#include <iostream>
#include "Settings.h"
#include "Log.h"

Client::Client()
{
    //ctor
}

void Client::init()
{
    sf::Socket::Status status = socket.connect(Settings::clientIp, Settings::port);
    if(status != sf::Socket::Done)
    {
        BP_LOG_ERROR("Unable to connect to socket");
    } 
    
}

void Client::clean()
{

}

void Client::handleEvents()
{

}


bool Client::update()
{
    
    //std::cout << "Client Update" << std::endl;
    sf::Socket::Status status = socket.connect(Settings::clientIp, Settings::port);
    if(status != sf::Socket::Done)
    {
        BP_LOG_ERROR("Unable to connect to socket");
    } 


    return true;
}

bool Client::isConnected()
{
    return connected;
}


sf::Packet Client::recieve()
{

}

Client::~Client()
{
    //dtor
}
