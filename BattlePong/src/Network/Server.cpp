#include "Network/Server.h"
#include <iostream>
#include "Settings.h"
#include "Log.h"
#include <cassert>

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

void Server::send(std::shared_ptr<PongFrame> frame)
{
    sf::Packet packet;
    packet << frame->ball->getPosition().x;
    packet << frame->ball->getPosition().y;
    packet << frame->leftPaddle->getPosition().x;
    packet << frame->leftPaddle->getPosition().y;
    packet << frame->rightPaddle->getPosition().x;
    packet << frame->rightPaddle->getPosition().y;
    packet << frame->userMessage.getString().toAnsiString();
    packet << frame->paddle1Hud->getScore();
    packet << frame->paddle2Hud->getScore();
    packet << frame->isSystemPaused();
    packet << frame->isPaused();
    packet << Settings::dimensions.x;
    packet << Settings::dimensions.y;

    if(socket.send(packet) != sf::Socket::Done)
    {
        BP_LOG_ERROR("Failed to send message");
    }
    
}


unsigned Server::numberConnections() const
{
    return connectionCount;
}

bool Server::isConnected()
{
    return connectionCount;
}

void Server::connect()
{
    if(!isConnected())
    {
        
        if(listener.accept(socket) == sf::Socket::Done)
        {
            connectionCount = connectionCount + 1;
        }
    }
    
}

void Server::disconnect()
{
    assert(isConnected());
    socket.disconnect();
}

sf::Packet Server::recieve()
{

}

Server::~Server()
{
    //dtor
    if(isConnected())
        socket.disconnect();
}
