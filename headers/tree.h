
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#include<assert.h>
#include<errno.h>
#include<fcntl.h>
#pragma GCC diagnostic ignored "-Wunused-result"
#pragma GCC diagnostic ignored "-Wstringop-truncation"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#pragma GCC diagnostic push

#define TagRoot 1
#define TagNode 2
#define TagLeaf 4
#define NoError 0
#define EXAMPLEFILE "./wl.txt"
#define reterr(x)\
    errno=(x);\
    return nullptr

#define Prints(x)\
        zero(buf,255);\
        strncpy((char*)buf,(char*)(x),255);\
        size = (int16)strlen((char*)buf);\
        if(size)\
            write(fd,buf,size)



typedef unsigned int int32;
typedef unsigned short int int16;
typedef unsigned char int8;
typedef struct s_leaf{
    int8 tag;
    struct u_tree *west;
    struct s_leaf *east;
    int8 key[128];
    int8 *value;
    int16 size;
} Leaf;
typedef struct s_node{
    int8 tag;
    struct s_node *north;          
    struct s_node *west;
    struct s_leaf *east;           
    int8 path[256];
} Node;

typedef struct u_tree{
    Node n;
    Leaf l;
 } Tree;
 Tree root = {
    .n = {
    .tag = (TagRoot|TagNode),
    .north = (Node*)&root,
    .west = 0,
    .east = 0,
    .path = "/"
    }
};
void zero(int8*,int16);
int8* indent(int8);
void print_tree(int,Tree *);
Leaf* find_last_linear(Node*);
Node* find_node_linear(int8*);
int8* lookup_linear(int8*,int8*);
Leaf* find_leaf_linear(int8*,int8*);
int8* example_path(int8);
