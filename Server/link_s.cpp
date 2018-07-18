//
// Created by PC on 2017/6/18.
//

#include <afxres.h>
#include "link_s.h"
#include "StandardDef.h"
void link_s::Init()
{
    sock_listen=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

    memset(&addr_listen,0, sizeof(sockaddr_in));
    addr_listen.sin_family=AF_INET;
    addr_listen.sin_port=htons(SERVER_LISTEN_PORT);
    addr_listen.sin_addr.S_un.S_addr=inet_addr(SERVER_IP);

}
void link_s::Destort()
{
    closesocket(sock_listen);
}
