//
// Created by PC on 2017/6/15.
//



#include <cstdint>
#include <fstream>
#include "sha1.h"
#ifndef P2P_CLIENT_FILE_HASH_H
#define P2P_CLIENT_FILE_HASH_H

#endif //P2P_CLIENT_FILE_HASH_H
using namespace std;
class file_hash
{
public:
    static void Get_file_hash(fstream & f, char *output);
};