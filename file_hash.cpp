//
// Created by PC on 2017/6/15.
//

#include "file_hash.h"

void file_hash::Get_file_hash(fstream & f,char * output)
{
    int len=f.rdbuf()->in_avail();
    uint8_t buf[len];
    f.read((char *)buf,len);
    SHA1 sha1;
    sha1.SHA_GO(buf,len,output);
}