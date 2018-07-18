//
// Created by PC on 2017/6/14.
//

#include <cstdio>
#include <winsock.h>
#include <fstream>
#include <assert.h>
#include <sstream>
#include "peerResponse.h"
#include "link.h"

peerResponse::peerResponse()
{

}
bool peerResponse::Get_file_from(SOCKET &sor_socket,fstream & file)
{
    char buf[LEN_PER_TRANS];
    int len=0;
    while ((len=recv(sor_socket,buf,LEN_PER_TRANS,0))>0)
    {
        file.write(buf,len);
    }
}
long peerResponse::Get_file(char* path,char * filename)//////////////////////////////==============
{
    assert(filename!=NULL);
    int len=peerIP_List.size();
    string f_shared_abslute_path=path;
    f_shared_abslute_path.append("\\").append(filename);
    for(int i=0;i<len-1;i++)
    {
        SOCKET socket_TCP;
        SOCKADDR_IN sockaddr_peer;
        link_client::Set_addr_des_peer(socket_TCP,sockaddr_peer,(peerIP_List[i]).c_str());
        connect(socket_TCP,(SOCKADDR*)&sockaddr_peer, sizeof(SOCKADDR));
        send(socket_TCP,filename,strlen(filename),0);
        fstream fs_local_save(f_shared_abslute_path,ios_base::binary|ios_base::out);
        bool ret=Get_file_from(socket_TCP,fs_local_save);
        if(ret)
        {
            long len_of_file= fs_local_save.rdbuf()->in_avail();
            assert(len_of_file==atoi(peerIP_List.back().c_str()));
            fs_local_save.close();
            closesocket(socket_TCP);
            return len_of_file;
        } else
        {
            fs_local_save.close();
            closesocket(socket_TCP);
        }

    }
    return -1;

}
bool peerResponse::Push_file(SOCKET & des_socket,char* path,char *filename)
{
    assert(filename!=NULL);
    fstream f;
    sharedFileLibrary::Search_file(path,filename,f);
    char buf[LEN_PER_TRANS];
    int len=0;
    while(!f.eof())
    {
        len=f.rdbuf()->in_avail();
        f.read(buf,LEN_PER_TRANS);
        send(des_socket,buf,len,0);
    }
    shutdown(des_socket,0);
    f.close();
}

vector<string>  peerResponse::splitWithStl(const std::string &str,const std::string &pattern)
{
    std::vector<std::string> resVec;

    if ("" == str)
    {
        return resVec;
    }
    //方便截取最后一段数据
    std::string strs = str + pattern;

    size_t pos = strs.find(pattern);
    size_t size = strs.size();

    while (pos != std::string::npos)
    {
        std::string x = strs.substr(0,pos);
        resVec.push_back(x);
        strs = strs.substr(pos+1,size);
        pos = strs.find(pattern);
    }

    return resVec;
}
bool peerResponse::Set_peerIP_list(char * receive_string)
{
    string s(receive_string);
    vector<string> v=splitWithStl(s," ");
    int len=v.size();
    if(len>0) {
        for(int i=0;i<len;i++)
        {
            peerIP_List.push_back(v[i]);
        }
        Print_peerIP_list();
        return true;
    }
    else
        return false;
}
void peerResponse::Print_peerIP_list()
{
    int peer_num=peerIP_List.size();
    if(peer_num>0)
    {
        printf("The IP List of peers who have the request file shows as follow:\n");
        printf("Total %d IP addresses\n",peer_num-1);
        for(int i=0;i<peer_num-1;i++)
        {
            printf("%d:\t %s \n",i,peerIP_List[i].c_str());
        }
        printf("File length:%s\n",peerIP_List[peer_num-1].c_str());
    }
    else
    {
        printf("No peer has the request file!\n");
    }
}