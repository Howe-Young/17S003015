//
// Created by PC on 2017/6/14.
//
#include <afxres.h>
#include "link.h"
link_client::link_client()
{

}

bool link_client::Init()
{
    sock_listen_peer=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    sock_client=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);


    memset(&addr_server,0, sizeof(SOCKADDR_IN));
    addr_server.sin_family=AF_INET;
    addr_server.sin_port=htons(SERVER_LISTEN_PORT);
    addr_server.sin_addr.S_un.S_addr=inet_addr(SERVER_IP);


    memset(&addr_listen_peer,0, sizeof(SOCKADDR_IN));
    addr_listen_peer.sin_family=AF_INET;
    addr_listen_peer.sin_port=htons(PEER_LISTEN_PORT);
    addr_listen_peer.sin_addr.S_un.S_addr=inet_addr(CLIENT_IP);


}
bool link_client::Destory()
{
    closesocket(sock_client);
    closesocket(sock_listen_peer);
}
bool link_client::Set_addr_des_peer(SOCKET &socket1,SOCKADDR_IN &sockaddr_in1,const char *IP)
{
    socket1=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    memset(&sockaddr_in1,0, sizeof(SOCKADDR_IN));
    sockaddr_in1.sin_family=AF_INET;
    sockaddr_in1.sin_port=htons(PEER_LISTEN_PORT);
    sockaddr_in1.sin_addr.S_un.S_addr=inet_addr(IP);
}