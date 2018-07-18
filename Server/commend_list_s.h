//
// Created by PC on 2017/6/18.
//

#ifndef P2P_SERVER_COMMEND_LIST_S_H
#define P2P_SERVER_COMMEND_LIST_S_H

#endif //P2P_SERVER_COMMEND_LIST_S_H
#include "StandardDef.h"
#include <vector>
#include <string>
#include "sqlite3.h"
using namespace std;
class commend_list_s
{
public:
    vector<string> list={"ADD","DELETE","LIST","QUIT","REQUEST"};
    int commend_total_types=5;
    static bool Form_add_sql(char *filename,char *IP,char *hash_val,int file_len,char *sql);
    static bool Form_del_sql(char *filename,char *hash_val,char *sql);
    static bool Form_list_sql(char *sql);
    static bool Form_req_sql(char *filename,char *sql);
    static bool Excute_sql(int commend_type,char * sql,char * someMsg);
    static bool Form_return_s_msg(bool sql_result,int comment_type,char *result,char * someMsg);
};