#include "Network/Client.h"
#include <iostream>
#include "Settings.h"
#include "Log.h"
#include <cassert>

Client::Client()
{
    //ctor
}

void Client::init()
{
    connect(Settings::clientIp, Settings::port);
}

void Client::connect(const std::string &ip, const unsigned &port)
{
    connected = false;
    if(socket.connect(ip, port) == sf::Socket::Done)
    {
        connected = true;
    } 

}


void Client::clean()
{

}

void Client::handleEvents()
{

}

bool Client::send(std::shared_ptr<PongFrame> frame)
{
    sf::Packet packet;
    packet << frame->rightPaddle;
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

bool Client::recieve(std::shared_ptr<PongFrame> frame)
{
    sf::Packet packet;
    if(socket.receive(packet) == sf::Socket::Done)
    {
        
        packet >> frame->ball;
        packet >> frame->leftPaddle;
        packet << frame->paddle1Hud->getScore();
        packet << frame->paddle2Hud->getScore();
        packet << Settings::systemPaused; 
        packet << Settings::playerPaused; 
        packet << Settings::dimensions.x;
        packet << Settings::dimensions.y;

/*
        //Set user message 
        std::string userMessage;
        packet >> userMessage;
        frame->userMessage.setString(userMessage);
*/
        //Set Player Score    
        sf::Uint32 player1score;
        sf::Uint32 player2score;
        packet >> player1score; 
        packet >> player2score; 
        frame->paddle1Hud->setScore(player1score);   
        frame->paddle2Hud->setScore(player2score);   


        //Set the system pause status 
        packet >> Settings::systemPaused;


        //Set the player pause status
        packet >> Settings::playerPaused;


        //Set the resolution of the game
        packet >> Settings::dimensions.x; 
        packet >> Settings::dimensions.y; 
        return true;
    }
    else
    {
        BP_LOG_ERROR("Client::recieve message failed");
        return false;
    } 
}

bool Client::update()
{
    
    return true;
}

bool Client::isConnected()
{
    return connected;
}

void Client::disconnect()
{
    assert(isConnected());
    socket.disconnect();
}

Client::~Client()
{
    //dtor
    if(isConnected()) 
        socket.disconnect();
}
