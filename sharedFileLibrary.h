//
// Created by PC on 2017/6/14.
//

#ifndef P2P_CLIENT_SHAREDFILELIBRARY_H
#define P2P_CLIENT_SHAREDFILELIBRARY_H

#endif //P2P_CLIENT_SHAREDFILELIBRARY_H

#include <stdio.h>
#include <vector>
#include "StandardDef.h"

using namespace std;
class sharedFileLibrary
{
public:
    sharedFileLibrary();
    int Get_num_shared_files();
    void Set_shared_dictionary_path(char* path,int len);
    char *Get_shared_dictionary_path();
    void Statistic_shared_file_list(char* path,int len);
    void Print_shared_file_list();
    static bool Search_file(char* path,char *filename,fstream &pFile);
private:
    int num_shared_files=0;
    char shared_dictionary_path[LEN_FILE_PATH]="..\\..\\c_shared_dictionary";
    vector<string> shared_file_list;
    void Set_num_shared_files(int num);
};