#include "Server.h"
#include <iostream>

Server::Server()
{
    //ctor
}

bool Server::connect()
{
    if (listener.listen(port) != sf::Socket::Done)
    {
        std::cerr << "unable to listen on port " << port << std::endl;
        return false;
    }


    if (listener.accept(socket) != sf::Socket::Done)
    {
        std::cerr << "unable to accept a connection on port " << port << std::endl;
        return false;
    }


    return true;
}

bool Server::isConnected()
{
    return connected;
}


sf::Packet Server::recieve()
{

}

Server::~Server()
{
    //dtor
}
