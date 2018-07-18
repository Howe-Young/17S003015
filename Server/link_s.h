//
// Created by PC on 2017/6/18.
//

#include <winsock2.h>

#ifndef P2P_SERVER_LINK_S_H
#define P2P_SERVER_LINK_S_H

#endif //P2P_SERVER_LINK_S_H
class link_s
{
public:
    SOCKET sock_listen;
    SOCKADDR_IN addr_listen;
    void Init();
    void Destort();
};