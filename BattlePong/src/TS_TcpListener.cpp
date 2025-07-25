#include "TS_TcpListener.h"
#include "TS_TcpSocket.h"

TS_TcpListener::TS_TcpListener()
{

}

sf::Socket::Status TS_TcpListener::listen(unsigned short port, const sf::IpAddress &address)
{
    std::lock_guard<std::mutex> lock(mutex);
    return listener.listen(port, address);
}

sf::Socket::Status TS_TcpListener::accept(TS_TcpSocket &client)
{
    std::lock_guard<std::mutex> lock(mutex);
    return listener.accept(client.socket);
}

void TS_TcpListener::setBlocking(bool blocking)
{
    std::lock_guard<std::mutex> lock(mutex);
    listener.setBlocking(blocking);
}

bool TS_TcpListener::isBlocking()
{
    std::lock_guard<std::mutex> lock(mutex);
    return listener.isBlocking();
}

TS_TcpListener::~TS_TcpListener()
{

}


