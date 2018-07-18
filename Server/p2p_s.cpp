//
// Created by PC on 2017/6/18.
//
#include <pthread.h>
#include <cstdio>
#include <sstream>
#include "p2p_s.h"



void myTask::run() {
    SOCKET client_sock =*((SOCKET*) arg1);
    SOCKADDR_IN client_addr=*((SOCKADDR_IN*)arg2);

    bool shut_flag = false;
    while (!shut_flag) {
        char recvbuf[LEN_COMMEND_C];
        memset(recvbuf, '\0', LEN_COMMEND_C);
        int len = recv(client_sock, recvbuf, LEN_COMMEND_C, 0);

        if(len>0) {
            int ret = 0;
            char *ptr = recvbuf;
            switch (ptr[0]) {
                case 'A':
                    ret = strncmp(ptr, "ADD", 3);
                    if (0 == ret) {
                        int shift = 4;
                        size_t sub_len = 0;
                        char filename[LEN_FILE_NAME];
                        memset(filename, '\0', LEN_FILE_NAME);
                        while (ptr[shift + sub_len] != ' ' && ptr[shift + sub_len] != '\0') {
                            sub_len++;
                        }
                        memcpy(filename, (ptr + shift), sub_len);

                        shift += (sub_len + 1);
                        sub_len = 0;
                        char hash_val[41];
                        while (ptr[shift + sub_len] != ' ' && ptr[shift + sub_len] != '\0') {
                            sub_len++;
                        }
                        memcpy(hash_val, (ptr + shift), sub_len);

                        shift += (sub_len + 1);
                        sub_len = 0;
                        int file_len = 0;
                        while (ptr[shift + sub_len] != ' ' && ptr[shift + sub_len] != '\0') {
                            sub_len++;
                        }
                        stringstream s;
                        s<<(ptr+shift);
                        s>>file_len;


                        char sql[LEN_SQL];
                        memset(sql, '\0', LEN_SQL);
                        commend_list_s::Form_add_sql(filename, inet_ntoa(client_addr.sin_addr), hash_val, file_len,
                                                     sql);

                        char someMsg[LEN_MSG_S];
                        memset(someMsg, '\0', LEN_MSG_S);
                        bool sql_result = commend_list_s::Excute_sql(1, sql, someMsg);

                        char result[LEN_MSG_S];
                        memset(result, '\0', LEN_MSG_S);
                        commend_list_s::Form_return_s_msg(sql_result, 0, result, someMsg);

                        send(client_sock, result, sizeof(result), 0);
                        printf("Add file done!------\n");

                    }
                    continue;
                case 'D':
                    ret = strncmp(ptr, "DELETE", 6);
                    if (0 == ret) {
                        int shift = 7;
                        size_t sub_len = 0;
                        char filename[LEN_FILE_NAME];
                        memset(filename, '\0', LEN_FILE_NAME);
                        while (ptr[shift + sub_len] != ' ' && ptr[shift + sub_len] != '\0') {
                            sub_len++;
                        }
                        memcpy(filename, (ptr + shift), sub_len);

                        shift += (sub_len + 1);
                        sub_len = 0;
                        char hash_val[41];
                        while (ptr[shift + sub_len] != ' ' && ptr[shift + sub_len] != '\0') {
                            sub_len++;
                        }
                        memcpy(hash_val, (ptr + shift), sub_len);

                        char sql[LEN_SQL];
                        memset(sql, '\0', LEN_SQL);
                        commend_list_s::Form_del_sql(filename, hash_val, sql);

                        char someMsg[LEN_MSG_S];
                        memset(someMsg, '\0', LEN_MSG_S);
                        bool sql_result = commend_list_s::Excute_sql(1, sql, someMsg);

                        char result[LEN_MSG_S];
                        memset(result, '\0', LEN_MSG_S);
                        commend_list_s::Form_return_s_msg(sql_result, 1, result, someMsg);

                        send(client_sock, result, sizeof(result), 0);
                        printf("Delete file done!------\n");

                    }
                    continue;
                case 'L':
                    ret = strncmp(ptr, "LIST", 4);
                    if (0 == ret) {
                        char sql[LEN_SQL];
                        memset(sql, '\0', LEN_SQL);
                        commend_list_s::Form_list_sql(sql);

                        char someMsg[LEN_MSG_S];
                        memset(someMsg, '\0', LEN_MSG_S);
                        bool sql_result = commend_list_s::Excute_sql(0, sql, someMsg);

                        char result[LEN_MSG_S];
                        memset(result, '\0', LEN_MSG_S);
                        commend_list_s::Form_return_s_msg(sql_result, 2, result, someMsg);

                        send(client_sock, result, sizeof(result), 0);
                        printf("Search file done!------\n");

                    }
                    continue;
                case 'Q':
                    ret = strncmp(ptr, "QUIT", 4);
                    if (0 == ret) {
                        shut_flag = true;
                        printf("Shut link!------\n");
                    }
                    continue;
                case 'R':
                    ret = strncmp(ptr, "REQUEST", 7);
                    if (0 == ret) {
                        int shift = 8;
                        size_t sub_len = 0;
                        char filename[LEN_FILE_NAME];
                        memset(filename, '\0', LEN_FILE_NAME);
                        while (ptr[shift + sub_len] != ' ' && ptr[shift + sub_len] != '\0') {
                            sub_len++;
                        }
                        memcpy(filename, (ptr + shift), sub_len);


                        char sql[LEN_SQL];
                        memset(sql, '\0', LEN_SQL);
                        commend_list_s::Form_req_sql(filename, sql);

                        char someMsg[LEN_MSG_S];
                        memset(someMsg, '\0', LEN_MSG_S);
                        bool sql_result = commend_list_s::Excute_sql(0, sql, someMsg);

                        char result[LEN_MSG_S];
                        memset(result, '\0', LEN_MSG_S);
                        commend_list_s::Form_return_s_msg(sql_result, 4, result, someMsg);

                        send(client_sock, result, sizeof(result), 0);
                        printf("Search IP-File done!------\n");

                    }
                    continue;

                default:
                    printf("Receive undefined commend!------\n");
                    break;
            }
        }
    }
    closesocket(client_sock);
}

void p2p_Server::exec_thread()
{
    Init_link_sock();
    pthread_t th_server;
    pthread_create(&th_server,NULL,run_server,this);
    pthread_join(th_server,NULL);
    Destory_link_sock();
}
void* p2p_Server::run_server(void * param)
{
    printf("Server is starting!\n");

    p2p_Server *p=(p2p_Server*)param;
    bind(p->link_s1.sock_listen,(SOCKADDR*)&p->link_s1.addr_listen, sizeof(SOCKADDR));

    printf("Start listening!\n");
    listen(p->link_s1.sock_listen,NUM_LINK);

    printf("Start thread pool!\n");
    p->thread_pool1.start();

    printf("Running!\n");
    while(true) {
        SOCKADDR_IN client_Addr;
        int size = sizeof(client_Addr);
        SOCKET client_Sock = accept(p->link_s1.sock_listen, (SOCKADDR *) &client_Addr, &size);


        myTask task;
        task.setArg((void*)&client_Sock,(void*)&client_Addr,NULL);
        int ret = p->thread_pool1.addTask((Task *) &task);
        if (ret)
            printf("Accept a client !\n");
        else {
            printf("Can't accept a client link!\n");
            char result[LEN_MSG_S], someMsg[LEN_MSG_S] = "Reject by server!";
            memset(someMsg, '\0', LEN_MSG_S);
            commend_list_s::Form_return_s_msg(false,3, result, someMsg);
            send(client_Sock, result, strlen(result), 0);
            closesocket(client_Sock);
        }
    }
}

void p2p_Server::Init_link_sock()
{
    link_s1.Init();
}
void p2p_Server::Destory_link_sock()
{
    link_s1.Destort();
}