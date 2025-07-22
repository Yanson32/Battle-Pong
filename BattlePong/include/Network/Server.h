#ifndef SERVER_H
#define SERVER_H
/*************************************************************************
*                           COPYRIGHT NOTICE
* Battle Pong is a clone of the classic pong game.
* Copyright (C) 2017 Wayne J Larson Jr. 
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 3 as 
* published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
***************************************************************************/
#include <SFML/Network.hpp>
#include <memory>
#include "Engin/PongFrame.h"

class Server
{
    public:
        Server();
        bool isConnected();
        void connect();
        void init();
        void clean();
        void handleEvents();
        bool update();
        void send(const sf::Uint32 &num);
        void send(std::shared_ptr<PongFrame> frame);
        sf::Packet recieve();
        virtual ~Server();
    protected:
    private:
        sf::TcpListener listener;
        sf::TcpSocket socket;
        bool connected = false;
        sf::IpAddress address;
};

#endif // CLIENTSERVER_H
