#include <iostream>

#include <pthread.h>
#include "p2p_c.h"
// Created by PC on 2017/6/14.
//

void p2pClient::Init_link_socket()
{
    link_client1.Init();
}
void p2pClient::Destory_link_socket()
{
    link_client1.Destory();
}
void p2pClient::exec_thread()
{
    Init_link_socket();
    pthread_t p1,p2;
    pthread_create(&p1,NULL,run_p2plisten,(void *)this);
    pthread_create(&p2,NULL,run_p2pclient,(void *)this);

    //pthread_join(p1,NULL);
    pthread_join(p2,NULL);
    Destory_link_socket();
}
void* p2pClient::run_p2plisten( void* param)
{
    p2pClient * p=(p2pClient *)param;
    bind(p->link_client1.sock_listen_peer,(SOCKADDR*)&p->link_client1.addr_listen_peer,sizeof(SOCKADDR));
    while (true)
    {
        listen(p->link_client1.sock_listen_peer,5);

        SOCKADDR peerAddr;
        int nSize= sizeof(SOCKADDR);

        SOCKET peerSock=accept(p->link_client1.sock_listen_peer,(SOCKADDR*)&peerAddr,&nSize);
        cout<<"\n=======accept========="<<endl;

        char receive_string[LEN_FILE_NAME];
        memset(receive_string,'\0',LEN_FILE_NAME);
        int len=recv(peerSock,receive_string,LEN_FILE_NAME,0);
        cout<<"\n========receive========"<<endl;
        char* path=p->sharedFileLibrary1.Get_shared_dictionary_path();
        cout<<"\n========transport========"<<endl;
        p->peerResponse1.Push_file(peerSock,path,receive_string);
        closesocket(peerSock);
        cout<<"\n========done========"<<endl;
        cout<<"Input commend index :";
    }
}
void* p2pClient::run_p2pclient( void* param)
{
    p2pClient * p=(p2pClient *)param;
    cout<<"Clint application start running!"<<endl;

    ////===================
    char shared_path[LEN_FILE_PATH];
    memset(shared_path,'\0',LEN_FILE_PATH);
    memcpy(shared_path,p->sharedFileLibrary1.Get_shared_dictionary_path(),strlen(p->sharedFileLibrary1.Get_shared_dictionary_path()));

    cout<<"Statistic shared files at "<<shared_path<<" ..."<<endl;
    p->sharedFileLibrary1.Statistic_shared_file_list(shared_path,strlen(shared_path));


    bool exit_flag= false;
    char request_filename[LEN_FILE_NAME];

    ///===========link to server
    int ret=-1;
    while (ret==-1) {
        ret = connect(p->link_client1.sock_client, (SOCKADDR *) &(p->link_client1.addr_server),
                      sizeof(p->link_client1.addr_server));
        if (-1 == ret) {
            cout << "Can't link to server!" << endl;
        }
    }
    while (!exit_flag)
    {
        ////==================
        cout<<"Commend list"<<endl;
        for(auto it=p->commend1.commend_list1.list.begin();it!=p->commend1.commend_list1.list.end();it++)
        {
            cout<<it-p->commend1.commend_list1.list.begin()<<"\t"<<*it<<endl;
        }


        ///////===============Form commend string=====
        cout<<"Input commend index :";
        cin>>p->commend1.commend_type;
        char commend_string[LEN_COMMEND_C];
        char receive_string[LEN_MSG_S];
        char filename[LEN_FILE_NAME];
        bool fret= false;
        int times=3;


        if(p->commend1.commend_type==0)///=====add
        {
            p->sharedFileLibrary1.Print_shared_file_list();

            while (!fret && times > 0) {

                cout << "Input filename needed to upload:";
                cin >> filename;
                memset(commend_string, '\0', LEN_COMMEND_C);
                fret = p->commend1.commend_list1.Form_add_c_msg(shared_path, filename, strlen(filename),
                                                                commend_string);
                if (!fret)
                    cout << "No this file!" << endl;
                times--;
            }
            if (0 == times) {
                cout << "Try later,please!";
                times=3;
            }
        }
        else if(p->commend1.commend_type==1) {        ///=====delete
            p->sharedFileLibrary1.Print_shared_file_list();
            while (!fret && times > 0) {
                cout << "Input filename needed to delete:";
                cin >> filename;
                memset(commend_string, '\0', LEN_COMMEND_C);
                fret = p->commend1.commend_list1.Form_del_c_msg(shared_path, filename, strlen(filename),
                                                                commend_string);
                if (!fret)
                    cout << "No this file!" << endl;
                times--;
            }
            if (0 == times)
                cout << "Try later,please!";
        }
        else if(p->commend1.commend_type==2) { ///=====list
            memset(commend_string, '\0', LEN_COMMEND_C);
            p->commend1.commend_list1.Form_list_c_msg(commend_string);
        }
        else if(p->commend1.commend_type==3) {///=====quit
            memset(commend_string, '\0', LEN_COMMEND_C);
            p->commend1.commend_list1.Form_quit_c_msg(commend_string);
        }
        else if(p->commend1.commend_type==4) {      ///=====request
            cout << "Input the name of the file you want:";
            cin >> request_filename;
            if (0 == strlen(request_filename))
                cout << "ERROR:Request filename can't be empty" << endl;
            else {
                memset(commend_string, '\0', LEN_COMMEND_C);
                p->commend1.commend_list1.Form_req_c_msg(request_filename, strlen(request_filename),
                                                         commend_string);
            }
        }
        else {
            exit_flag = true;
            cout << "Exit client app!" << endl;
        }

        if(p->commend1.commend_type!=3)
        {

            cout<<"Connect to server successfully!"<<endl;
            send(p->link_client1.sock_client,commend_string,strlen(commend_string),0);

            memset(receive_string,'\0',LEN_MSG_S);
            int len_recv=recv(p->link_client1.sock_client,receive_string,LEN_MSG_S,0);
            cout<<"Response of server:\t"<<receive_string<<endl;

            if(4==p->commend1.commend_type)
            {
                p->peerResponse1.Set_peerIP_list(receive_string);
                int file_len=atoi(p->peerResponse1.peerIP_List[p->peerResponse1.peerIP_List.size()-1].c_str());
                int file_saved_len=p->peerResponse1.Get_file(shared_path,request_filename);
                if(file_len==file_saved_len)
                    cout<<"Request file already downloaded!"<<endl;
                p->peerResponse1.peerIP_List.clear();
            }
            else if(0==p->commend1.commend_type)
            {
                if(len_recv>0)
                    cout<<receive_string<<endl;
            }
            else if(1==p->commend1.commend_type)
            {
                if(len_recv>0)
                    cout<<receive_string<<endl;
            }
            else if(2==p->commend1.commend_type)
            {
                if(len_recv>0) {
                    cout << receive_string << endl;
                }
            }

        } else if(p->commend1.commend_type==3){
            send(p->link_client1.sock_client,commend_string,strlen(commend_string),0);
            exit_flag=true;
        }
    }

    cout<<"p2pclient exit!Thx for use"<<endl;
    ////================

}