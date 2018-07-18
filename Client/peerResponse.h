//
// Created by PC on 2017/6/14.
//

#include <vector>
#include <winsock2.h>
#include "sharedFileLibrary.h"

#ifndef P2P_CLIENT_PEER_RESPONSE_H
#define P2P_CLIENT_PEER_RESPONSE_H

#endif //P2P_CLIENT_PEER_RESPONSE_H

using namespace std;
class peerResponse
{
public:

    peerResponse();
    bool Get_file_from(SOCKET &sor_socket,fstream & file);
    long Get_file(char* path,char * filename);
    bool Push_file(SOCKET & des_socket,char* path,char *filename);
    bool Set_peerIP_list(char * receive_string);
    void Print_peerIP_list();
    vector<string> splitWithStl(const std::string &str,const std::string &pattern);
    vector<string> peerIP_List;
};