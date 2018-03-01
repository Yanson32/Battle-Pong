#include "Server.h"
#include <iostream>

Server::Server(const int newPort): port(newPort)
{
    //ctor
    listener.setBlocking(true);
}

void Server::init()
{
    std::cout << "Server::init " << std::endl;
    if (listener.listen(port) != sf::Socket::Done)
    {
        std::cerr << "unable to listen on port " << port << std::endl;
        return;
    }


    if (listener.accept(socket) != sf::Socket::Done)
    {
        std::cerr << "unable to accept a connection on port " << port << std::endl;
        return;
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


sf::Packet Server::recieve()
{

}

Server::~Server()
{
    //dtor
}
