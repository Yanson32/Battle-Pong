#include "Client.h"
#include <iostream>
#include "Events/EventManager.h"
#include "Events/ChangeState.h"

Client::Client(const sf::String newIp, const int newPort):
port(newPort),
ip(newIp)
{
    //ctor
    setTimeOut(sf::seconds(5));
}

bool Client::isConnected()
{

}

void Client::init()
{

    sf::Socket::Status status = socket.connect({ip}, port, sf::seconds(5));
    if (status != sf::Socket::Done)
    {
        // error...
        EventManager::inst().Post<ChangeState>(stateId::CONNECT_STATE);
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

}

void Client::setTimeOut(const sf::Time &newTime)
{
    timeOut = newTime;
}

Client::~Client()
{
    //dtor
}
