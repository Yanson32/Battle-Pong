#include "TS_TcpSocket.h"


TS_TcpSocket::TS_TcpSocket()
{

}

sf::Socket::Status TS_TcpSocket::send(sf::Packet &packet)
{
    std::lock_guard<std::mutex> lock(mutex);
    return socket.send(packet);

}

sf::Socket::Status TS_TcpSocket::receive(sf::Packet &packet)
{
    std::lock_guard<std::mutex> lock(mutex);
    return socket.receive(packet);
}

sf::Socket::Status TS_TcpSocket::connect(const sf::IpAddress &remoteAddress, unsigned short remotePort, sf::Time timeout)
{
    return socket.connect(remoteAddress, remotePort, timeout);
}

void TS_TcpSocket::disconnect()
{
    std::lock_guard<std::mutex> lock(mutex);
    socket.disconnect();
}


TS_TcpSocket::~TS_TcpSocket()
{

}

