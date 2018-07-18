//
// Created by PC on 2017/6/14.
//

#include <winsock2.h>
#include "StandardDef.h"
#ifndef P2P_CLIENT_LINK_H
#define P2P_CLIENT_LINK_H

#endif //P2P_CLIENT_LINK_H
class link_client
{
public:

    SOCKET sock_listen_peer;

    SOCKET sock_client;
    SOCKADDR_IN addr_listen_peer;
    SOCKADDR_IN addr_server;

    link_client();
    static bool Set_addr_des_peer(SOCKET &socket,SOCKADDR_IN &sockaddr_in1,const char *IP);
    bool Init();
    bool Destory();
};