#ifndef SERVER_H
#define SERVER_H
#include <SFML/Network.hpp>

class Server
{
    public:
        Server(const int newPort);
        bool isConnected();
        bool connect();
        sf::Packet recieve();
        virtual ~Server();
    protected:
    private:
        sf::TcpSocket socket;
        sf::TcpListener listener;
        bool connected = false;
        int port = 4000;
        sf::IpAddress address;
};

#endif // CLIENTSERVER_H
