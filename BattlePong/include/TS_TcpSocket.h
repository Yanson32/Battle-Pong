#ifndef TS_TCP_SOCKET
#define TS_TCP_SOCKET
#include <mutex>
#include <SFML/Network/TcpSocket.hpp>

class TS_TcpListener;
class TS_TcpSocket
{
    public:
        TS_TcpSocket();
        sf::Socket::Status send(sf::Packet &packet);
        sf::Socket::Status receive(sf::Packet &packet);
        sf::Socket::Status connect(const sf::IpAddress &remoteAddress, unsigned short remotePort, sf::Time timeout=sf::Time::Zero);
        void disconnect();
        virtual ~TS_TcpSocket();

    private:
        sf::TcpSocket socket;
        std::mutex mutex;
        friend class TS_TcpListener;
};

#endif

