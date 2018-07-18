#include <iostream>
#include "p2p_s.h"
int main() {
    WSADATA wsa;
    /*初始化socket资源*/
    if (WSAStartup(MAKEWORD(1,1),&wsa) != 0)
    {
        return -1;   //代表失败
    }

    p2p_Server p2p_server;
    p2p_server.exec_thread();

    WSACleanup();
    return 0;
}