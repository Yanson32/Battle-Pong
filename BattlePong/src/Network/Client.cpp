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

sf::Uint32 Client::recieve(sf::Uint32 &num)
{
    sf::Packet packet;

    socket.receive(packet);

    packet >> num;
    return num;
}

std::shared_ptr<PongFrame> Client::recieve(std::shared_ptr<PongFrame> frame)
{
    sf::Packet packet;
    socket.receive(packet);
    
    //Set Ball Position
    float ballPosition_x;
    float ballPosition_y;
    packet >> ballPosition_x; 
    packet >> ballPosition_y; 
    frame->ball->setPosition({ballPosition_x, ballPosition_y});


    //Set left Paddle position
    float leftPaddlePosition_x;
    float leftPaddlePosition_y;
    packet >> leftPaddlePosition_x;
    packet >> leftPaddlePosition_y;
    frame->leftPaddle->setPosition({leftPaddlePosition_x, leftPaddlePosition_y});


    //Set right paddle position
    float rightPaddlePosition_x;
    float rightPaddlePosition_y;
    packet >> rightPaddlePosition_x; 
    packet >> rightPaddlePosition_y;
    frame->rightPaddle->setPosition({rightPaddlePosition_x, rightPaddlePosition_y}); 

    //Set user message 
    std::string userMessage;
    packet >> userMessage;
    frame->userMessage.setString(userMessage);
    
//    packet >> frame->player1score;
//    packet >> frame->player2score;
    bool systemPause;
    packet >> systemPause;
    frame->systemPause(systemPause);

    bool playerPaused;
    packet >> frame->m_playerPaused;
    frame->pause(playerPaused);

//    packet >> frame->resolution_x;
//    packet >> frame->resolution_y;*/

    return frame;
}

bool Client::update()
{
    
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
