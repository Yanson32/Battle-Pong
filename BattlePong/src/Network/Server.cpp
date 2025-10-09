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
    listen(Settings::port);
}

void Server::listen(const unsigned &port)
{
    if(listener.listen(port) != sf::Socket::Done)
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

bool Server::send(std::shared_ptr<PongFrame> frame)
{
    sf::Packet packet;
    packet << frame->ball;
    packet << frame->leftPaddle;
    packet << frame->userMessageIndex;
    packet << frame->paddle1Hud;
    packet << frame->paddle2Hud;
    packet << Settings::systemPaused; 
    packet << Settings::playerPaused; 
    packet << Settings::dimensions.x;
    packet << Settings::dimensions.y;
   
    if(socket.send(packet) != sf::Socket::Done)
    {
        BP_LOG_ERROR("Failed to send message");
        return false;
    }
    return true; 
}


unsigned Server::numberConnections() const
{
    return connectionCount.getNumber();
}

bool Server::isConnected()
{
    return connectionCount.getNumber();
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

bool Server::recieve(std::shared_ptr<PongFrame> frame)
{
    sf::Packet packet;
    if(socket.receive(packet) == sf::Socket::Done)
    {
        packet >> frame->rightPaddle;

        //Set the system pause status 
        //packet >> Settings::systemPaused;


        //Set the player pause status
        packet >> Settings::playerPaused;


        //Set the resolution of the game
        packet >> Settings::dimensions.x; 
        packet >> Settings::dimensions.y;
        return true;
    } 
    else
    {
        BP_LOG_ERROR("Server::send message failed");
        return false;
    }

}

Server::~Server()
{
    //dtor
    if(isConnected())
        socket.disconnect();
}
