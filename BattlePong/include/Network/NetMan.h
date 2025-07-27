#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H
#include <string>
#include "Network/Server.h"
#include "Network/Client.h"


class NetMan
{
    public:
        Server server;
        Client client;
        int count = 0;
};

#endif
