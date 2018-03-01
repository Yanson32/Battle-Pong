#ifndef CLIENT_H
#define CLIENT_H

#include <SFML/Network.hpp>
#include <SFML/System/String.hpp>

class Client
{
    public:
        Client(const sf::String newIp, const int newPort);
        bool isConnected();
        void init();
        void clean();
        void handleEvents();
        bool update();
        void setTimeOut(const sf::Time &newTime);
        virtual ~Client();
    protected:
    private:
        const int port = 0;
        const sf::String ip;
        sf::TcpSocket socket;
        sf::Time timeOut;
};

#endif // CLIENT_H
