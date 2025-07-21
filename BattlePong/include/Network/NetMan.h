#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H
#include <string>
#include "Network/Server.h"
#include "Network/Client.h"


class NetMan
{
    public:
        NetMan();

        bool send(const std::string &msg);
        virtual ~NetMan();
    private:
        Server server;
        Client client;
};

#endif
