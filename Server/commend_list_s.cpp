//
// Created by PC on 2017/6/18.
//
#include <cstring>
#include <sstream>
#include <cstdio>
#include "commend_list_s.h"
bool commend_list_s::Form_add_sql(char *filename,char *IP,char *hash_val,int file_len,char *sql)
{
    stringstream stream;
    string name_db_table=NAME_DB_TABLE;
    stream<<file_len;
    string temp="INSERT INTO ";
    string len;
    stream>>len;
    temp.append(name_db_table).append("(Filename,IP,Hash,File_len) VALUES('").append(filename).append("','").append(IP).append("','").append(hash_val).append("',").append(len).append(")");
    memcpy(sql,temp.c_str(),strlen(temp.c_str()));
    printf("sql: %s\n",sql);
}
bool commend_list_s::Form_del_sql(char *filename,char *hash_val,char *sql)
{
    string name_db_table=NAME_DB_TABLE;
    string temp="DELETE FROM ";
    string len;
    temp.append(name_db_table).append(" WHERE Filename='").append(filename).append("' AND Hash='").append(hash_val).append("'");
    memcpy(sql,temp.c_str(),strlen(temp.c_str()));
    printf("sql: %s\n",sql);
}
bool commend_list_s::Form_list_sql(char *sql)
{
    string name_db_table=NAME_DB_TABLE;
    string temp="SELECT Filename FROM ";
    string len;
    temp.append(name_db_table);
    memcpy(sql,temp.c_str(),strlen(temp.c_str()));
    printf("sql: %s\n",sql);
}

bool commend_list_s::Form_req_sql(char *filename,char *sql)
{
    string name_db_table=NAME_DB_TABLE;
    string temp="SELECT IP,File_len FROM ";
    string len;
    temp.append(name_db_table).append(" WHERE Filename='").append(filename).append("'");
    memcpy(sql,temp.c_str(),strlen(temp.c_str()));
    printf("sql: %s\n",sql);
}
bool commend_list_s::Excute_sql(int commend_type,char * sql,char  *  someMsg)
{
    sqlite3 *db=NULL;
    int ret_db=sqlite3_open(PATH_DB,&db);
    if (SQLITE_OK != ret_db)

    {
        printf("No db file!");
        return false;
    }
    char **pazResult;
    int row=0,col=0;
    if(0==commend_type) ///查询
    {
        char *errMsg=NULL;
        int result=sqlite3_get_table(db,sql,&pazResult,&row,&col,&errMsg);
        if(errMsg)
            memcpy(someMsg,errMsg, strlen(errMsg));
        if(0==result)
        {
            for(int i=0;i<row;i++) {
                memcpy(someMsg+strlen(someMsg), pazResult[(i+1)*col+0], strlen(pazResult[(i+1)*col+0]));
                memcpy(someMsg+strlen(someMsg)," ",1);
            }
            if(col==2)
                memcpy(someMsg+strlen(someMsg),pazResult[1*col+1],strlen(pazResult[1*col+1]));
            sqlite3_free_table(pazResult);
            printf("search result: %s\n",someMsg);
            sqlite3_close(db);
            return true;
        }
        else
        {
            sqlite3_free_table(pazResult);
            sqlite3_close(db);
            return false;
        }
    }
    else if(1==commend_type)///增删改
    {
        char *errMsg=NULL;
        int result =sqlite3_exec(db,sql,0,0,&errMsg);
        if(errMsg)
            memcpy(someMsg,errMsg, strlen(errMsg));
        printf("sql result:%d\n",result);

        if(0==result)
        {
            result = sqlite3_exec(db, "COMMIT;", 0, 0, 0);
            printf("sql commit result:%d\n",result);
            if(1==result)
                printf("sql commit succeed!\n");
            else
                printf("sql commit failed!\n");

            sqlite3_close(db);
            return true;
        }
        else{
            sqlite3_close(db);
            return false;
        }
    }
}
bool commend_list_s::Form_return_s_msg(bool sql_result,int commend_type,char *result,char * someMsg)
{
    memset(result,'\0',LEN_MSG_S);
    if(sql_result)
    {
        switch (commend_type)
        {
            case 0:
                memcpy(result,"OK",2);
                break;
            case 1:
                memcpy(result,"OK",2);
                break;
            case 2:
                memcpy(result,someMsg,strlen(someMsg));
                break;
            case 3:
                break;
            case 4:
                memcpy(result,someMsg,strlen(someMsg));
                break;
            default:
                break;
        }
    }
    else
    {
        memcpy(result,"ERROR ",6);
        memcpy(result+6,someMsg,strlen(someMsg));
    }
    return true;
}