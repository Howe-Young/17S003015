//
// Created by PC on 2017/6/14.
//

#ifndef P2P_CLIENT_COMMEND_H
#define P2P_CLIENT_COMMEND_H

#endif //P2P_CLIENT_COMMEND_H

#include <vector>
#include <winsock2.h>
#include "StandardDef.h"
#include "commend_list.h"
using namespace std;
class commend
{
public:

    int commend_type;
    char filename[LEN_FILE_NAME];
    commend_list commend_list1;
    bool Send_commend(char*path,int commend_type,SOCKET &socket);
    int Receive_from_server(SOCKET &socket,char *result);
};