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
    std::cout << "Client Init " << std::endl;
    std::cout << "Client Port = " << Settings::port << std::endl;

    sf::Socket::Status status = socket.connect(Settings::clientIp, Settings::port);
    if(status != sf::Socket::Done)
    {
        BP_LOG_ERROR("Unable to connect to socket");
        std::cout << "Unable to connect to socket" << std::endl;
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
        std::cout << "Unable to connect to socket" << std::endl;
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
