#ifndef TS_Listener
#define TS_Listener
#include <mutex>
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/IpAddress.hpp>
class TS_TcpSocket;
class TS_TcpListener
{
    public:
        TS_TcpListener();
        sf::Socket::Status listen(unsigned short port, const sf::IpAddress &address=sf::IpAddress::Any);
        sf::Socket::Status accept(TS_TcpSocket &client);
        void setBlocking(bool blocking);
        bool isBlocking();
        virtual ~TS_TcpListener();
    private:
        sf::TcpListener listener; 
        std::mutex mutex;
};
#endif
