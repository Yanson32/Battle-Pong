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
    std::cout << "Server Init" << std::endl;
    std::cout << "Server Port = " << Settings::port << std::endl;
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
        
        std::cout << "Listening" << std::endl;
        if(listener.accept(socket) == sf::Socket::Done)
        {
            //BP_LOG_FATAL_ERROR("Unable to connect to client ");
            connected = true;
            std::cout << "Connected" << std::endl;

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
