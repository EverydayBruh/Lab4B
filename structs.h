#ifndef STRUCTS_H
#define STRUCTS_H

#include <ctype.h>


typedef char* KeyType;
typedef char* InfoType;



typedef struct Node {
    KeyType key;
    InfoType info;
    struct Node* left;
    struct Node* right;
    struct Node* par;
    int h;
} Node;

typedef struct Tree
{
    Node* root;
} Tree;



int addElement(Tree* tree, KeyType key, InfoType info);
KeyType readKey();
InfoType readInfo();
int printTree(Node* root, int step);
Node* findByKey(Node* root, KeyType key, int* k, int number);
Node* spetialSearch(Node* root, KeyType max, int number);
void printNode(Node* node);
int treeTraversal(Node* root, KeyType min, KeyType max);

int deleteNode(Tree* tree, KeyType key, int number);

int readFromFile(FILE* fb, Tree* tree);

int freeTree(Node* root);



#endif