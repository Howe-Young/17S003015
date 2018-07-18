//
// Created by PC on 2017/6/14.
//
#include <io.h>
#include <cstring>
#include <ios>
#include <assert.h>
#include <fstream>
#include <iostream>
#include "peerResponse.h"
sharedFileLibrary::sharedFileLibrary() {

}
int sharedFileLibrary::Get_num_shared_files()
{
    return num_shared_files;
}
void sharedFileLibrary::Set_num_shared_files(int num)
{
    num_shared_files=num;
}
void sharedFileLibrary::Set_shared_dictionary_path(char* path,int len)
{
    if(path)
        memcpy(shared_dictionary_path,path,len);
    else
        shared_dictionary_path[0]='\0';
}
char * sharedFileLibrary::Get_shared_dictionary_path()
{
    return shared_dictionary_path;
}
void getfiles(string path,vector<string> &files)
{
    long hFile=0;

    _finddata_t fileinfo;

    string p;
    if((hFile=_findfirst(p.assign(path).append("\\").append("*.*").c_str(),&fileinfo))!=-1)
    {
        do{
            if((fileinfo.attrib & _A_SUBDIR))
            {
                if(strcmp(fileinfo.name,".")!=0 && strcmp(fileinfo.name,"..")!=0)
                    getfiles(p.assign(path).append("\\").append(fileinfo.name),files);
            } else {
                string t=fileinfo.name;
                files.push_back(t);
            }
        }while (_findnext(hFile,&fileinfo)==0);
        _findclose(hFile);
    }
}
void sharedFileLibrary::Statistic_shared_file_list(char* path,int len)
{
    string p=path;
    getfiles(p,shared_file_list);
    Set_num_shared_files(shared_file_list.size());
}
void sharedFileLibrary::Print_shared_file_list()
{
    printf("Total %d shared files in shared dictionary!\n",shared_file_list.size());
    printf("Shared Files:\n");
    for(auto it=shared_file_list.begin();it!=shared_file_list.end();it++)
    {
        printf("%d\t",it-shared_file_list.begin());
        cout<<*it<<endl;
    }
}
bool sharedFileLibrary::Search_file(char* path,char *filename,fstream &pFile)
{
    assert(strlen(filename)<LEN_FILE_NAME);
    char file_absolute_path[LEN_FILE_PATH+LEN_FILE_NAME];
    memset(file_absolute_path,0,LEN_FILE_PATH+LEN_FILE_NAME);
    memcpy(file_absolute_path,path,strlen(path));
    memcpy(file_absolute_path+strlen(path),"\\",2);
    memcpy(file_absolute_path+strlen(file_absolute_path),filename,strlen(filename));
    pFile.open(file_absolute_path,ios_base::in|ios_base::binary);
    if(pFile.good())
    {
        printf("Open file %s successfully!\n",filename);
        return true;
    }
    else
    {
        printf("Open file %s fail!\n",filename);
        return false;
    }
}
