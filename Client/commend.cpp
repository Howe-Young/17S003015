//
// Created by PC on 2017/6/14.
//
#include <cstdio>
#include "commend.h"
bool commend::Send_commend(char*path,int commend_type,SOCKET &socket)///=====================
{
    printf("%s commend sending...\n",commend_list1.list[commend_type]);
    char msg[LEN_COMMEND_C];
    switch(commend_type)
    {
        case 0:commend_list1.Form_add_c_msg(path,filename,strlen(filename),msg);
            break;
        case 1:commend_list1.Form_del_c_msg(path,filename,strlen(filename),msg);
            break;
        case 2:commend_list1.Form_list_c_msg(msg);
            break;
        case 3:commend_list1.Form_quit_c_msg(msg);
            break;
        case 4:commend_list1.Form_req_c_msg(filename,strlen(filename),msg);
            break;
        default:
            printf("commend type error!\n");
            closesocket(socket);
            return false;
    }
    send(socket,msg,strlen(msg),0);
    closesocket(socket);
    return true;
}
int commend::Receive_from_server(SOCKET &socket,char *result)
{
    int len=0;
    int accum=0;
    char temp[48];
    while ((len=recv(socket,temp,48,0))>0) {
        memcpy(result + accum, temp, len);
        accum += len;
    }
    return accum;
}
