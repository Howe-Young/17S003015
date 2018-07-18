#include <iostream>
#include <pthread.h>
#include "p2p_c.h"
int main() {
    WSADATA wsa;
    /*初始化socket资源*/
    if (WSAStartup(MAKEWORD(1,1),&wsa) != 0)
    {
        return -1;   //代表失败
    }
    p2pClient p2pClient1;
    p2pClient1.exec_thread();

    WSACleanup();



    return 0;
}