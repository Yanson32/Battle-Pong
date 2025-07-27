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
    
        //Set Ball Position
        float ballPosition_x;
        float ballPosition_y;
        packet >> ballPosition_x; 
        packet >> ballPosition_y; 


        //Set left Paddle position
        float leftPaddlePosition_x;
        float leftPaddlePosition_y;
        packet >> leftPaddlePosition_x;
        packet >> leftPaddlePosition_y;


        //Set right paddle position
        float rightPaddlePosition_x;
        float rightPaddlePosition_y;
        packet >> rightPaddlePosition_x; 
        packet >> rightPaddlePosition_y;
        frame->rightPaddle->setPosition({rightPaddlePosition_x, rightPaddlePosition_y}); 

        //Set user message 
        std::string userMessage;
        packet >> userMessage;
        //frame->userMessage.setString(userMessage);

        //Set Player Score    
        sf::Uint32 player1score;
        sf::Uint32 player2score;
        packet >> player1score; 
        packet >> player2score; 


        //Set the system pause status 
        bool systemPause;
        packet >> systemPause;
        //frame->systemPause(systemPause);


        //Set the player pause status
        //packet >> frame->m_playerPaused;


        //Set the resolution of the game
        //packet >> Settings::dimensions.x; 
        //packet >> Settings::dimensions.y; 
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
