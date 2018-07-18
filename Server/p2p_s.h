//
// Created by PC on 2017/6/18.
//

#include "link_s.h"
#include "sqlite3.h"
#include "thread_pool.h"
#include "StandardDef.h"
#include "commend_list_s.h"
#ifndef P2P_SERVER_P2P_S_H
#define P2P_SERVER_P2P_S_H

#endif //P2P_SERVER_P2P_S_H
using namespace WR;
class myTask:public Task
{
public:
    myTask(){};
    virtual void run();
};
class p2p_Server
{
public:

    link_s link_s1;
    thread_pool thread_pool1;

    void exec_thread();
    static void* run_server(void * param);

    void Init_link_sock();
    void Destory_link_sock();
};