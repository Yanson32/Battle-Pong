#include "Network/Server.h"
#include <iostream>
#include "Settings.h"
#include "Log.h"

Server::Server()
{
    //ctor
    listener.setBlocking(true);
}

void Server::init()
{
    if(listener.listen(Settings::port) != sf::Socket::Done)
    {
        BP_LOG_FATAL_ERROR("Unable to listen on port " + std::to_string(Settings::port));
    }
}

void Server::clean()
{

}

void Server::handleEvents()
{

}


bool Server::update()
{



    return true;
}

bool Server::isConnected()
{
    return connected;
}

void Server::connect()
{
    if(!connected)
    {
        
        if(listener.accept(socket) == sf::Socket::Done)
        {
            connected = true;
        }
    }
    
}

sf::Packet Server::recieve()
{

}

Server::~Server()
{
    //dtor
}
