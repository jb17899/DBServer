# **DBServer Tree Structure**

 **Overview**

This C program implements a tree-like data structure composed of Node and Leaf elements. It provides functions to create, traverse, and search the tree using linear algorithms. The implementation supports adding nodes and leaves dynamically, managing paths, and printing the structure in an indented format.


 **File Structure**

tree.h - Header file (assumed) that defines basic structures (Node, Leaf, Tree).

tree.c - Contains the main implementation of the tree logic.

main_tree - Entry point that builds and populates the tree.

**Main Structures Used**:Tree,Leaf,Node

typedef struct Node {
    int8 tag;
    struct Node* north;
    struct Node* west;
    struct Leaf* east;
    int8 path[256];
} Node;

typedef struct Leaf {
    int8 tag;
    struct Leaf* east;
    Tree* west;
    int8 key[128];
    int8* value;
    int16 size;
} Leaf;

typedef struct Tree {
    Node n;
    Leaf l;
} Tree;
