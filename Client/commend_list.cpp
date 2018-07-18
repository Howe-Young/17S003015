//
// Created by PC on 2017/6/16.
//

#include <cstring>
#include <sstream>
#include "file_hash.h"
#include "commend_list.h"
#include "sharedFileLibrary.h"

bool commend_list::Form_add_c_msg(char*path,char * filename,int len_name,char * result)
{
    if(!filename)
        return false;
    fstream f;
    sharedFileLibrary::Search_file(path,filename,f);
    if(!f.good())
        return false;
    int file_len=f.rdbuf()->in_avail();
    char hash_val[41];
    file_hash::Get_file_hash(f,hash_val);
    memset(result,'\0',LEN_COMMEND_C);
    memcpy(result,"ADD ",4);
    memcpy(result+4,filename,len_name);
    memcpy(result+strlen(result)," ",1);
    memcpy(result+strlen(result),hash_val,strlen(hash_val));
    memcpy(result+strlen(result)," ",1);
    stringstream s;
    s<<file_len;
    string file_len_s;
    s>>file_len_s;
    memcpy(result+strlen(result),file_len_s.c_str(), sizeof(int));
    return true;
}
bool commend_list::Form_del_c_msg(char*path,char * filename,int len_name,char * result)
{
    if(!filename)
        return false;
    fstream f;
    sharedFileLibrary::Search_file(path,filename,f);
    if(!f.good())
        return false;
    char hash_val[41];
    file_hash::Get_file_hash(f,hash_val);
    memset(result,'\0',LEN_COMMEND_C);
    memcpy(result,"DELETE ",7);
    memcpy(result+7,filename,len_name);
    memcpy(result+strlen(result)," ",1);
    memcpy(result+strlen(result),hash_val,strlen(hash_val));
    return true;
}
bool commend_list::Form_req_c_msg(char * filename,int len_name,char * result)
{
    if(!filename)
        return false;
    memset(result,'\0',LEN_COMMEND_C);
    memcpy(result,"REQUEST ",8);
    memcpy(result+8,filename,len_name);
    return true;
}
bool commend_list::Form_list_c_msg(char * result)
{
    memset(result,'\0',LEN_COMMEND_C);
    memcpy(result,"LIST",4);
    return true;
}
bool commend_list::Form_quit_c_msg(char * result)
{
    memset(result,'\0',LEN_COMMEND_C);
    memcpy(result,"QUIT",4);
    return true;
}
