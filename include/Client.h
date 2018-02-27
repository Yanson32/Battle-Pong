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
        virtual ~Client();
    protected:
    private:
        const int port = 0;
        const sf::String ip;
};

#endif // CLIENT_H
