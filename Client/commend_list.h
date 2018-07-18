//
// Created by PC on 2017/6/15.
//



#ifndef P2P_CLIENT_COMMEND_LIST_H
#define P2P_CLIENT_COMMEND_LIST_H

#endif //P2P_CLIENT_COMMEND_LIST_H

#include "StandardDef.h"
#include <vector>
#include <string>

using namespace std;
class commend_list
{
public:
    vector<string> list={"ADD","DELETE","LIST","QUIT","REQUEST"};
    int commend_total_types;
    commend_list():commend_total_types(list.size()){};
    bool Form_add_c_msg(char*path,char * filename,int len_name,char * result);
    bool Form_del_c_msg(char*path,char * filename,int len_name,char * result);
    bool Form_req_c_msg(char * filename,int len_name,char * result);
    bool Form_list_c_msg(char * result);
    bool Form_quit_c_msg(char * result);
};