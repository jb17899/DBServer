#ifndef CACHE22
#define CACHE22
#define _GNU_SOURCE



#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<assert.h>
#pragma GCC diagnostic ignored "-Wstringop-truncation"
#pragma GCC diagnostic push


#define HOST "127.0.0.1"
#define PORT "12049"




typedef unsigned int int32;
typedef unsigned short int int16;
typedef unsigned char int8;
typedef struct s_client{
    int s;
    char add[16];
    int16 port;
} Client;

typedef int32 (*Callback)(Client*,int8*,int8*);

typedef struct s_cmdhandler{
    int8* cmd;
    Callback handler;
} CmdHandler;
void mainloop(int);
int initserver(int16);
int main(int,char**);
#endif