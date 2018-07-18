//
// Created by PC on 2017/6/14.
//

#ifndef P2P_CLIENT_P2PCLIENT_H
#define P2P_CLIENT_P2PCLIENT_H

#endif //P2P_CLIENT_P2PCLIENT_H


#include "link.h"
#include "commend.h"
#include "peerResponse.h"


class p2pClient
{
public:
    link_client link_client1;
    commend commend1;
    peerResponse peerResponse1;
    sharedFileLibrary sharedFileLibrary1;
    void exec_thread();
    static void* run_p2plisten(void * param);
    static void* run_p2pclient( void* param);
    void Init_link_socket();
    void Destory_link_socket();
};