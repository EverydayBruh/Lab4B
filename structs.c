#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include "InOut.h"
#include "balance.h"

int keyCompare(KeyType key1, KeyType key2){
    return strcmp(key1, key2);
}

void freeNode(Node* node){
    free(node->info);
    free(node->key);
}

void printNode(Node* node){
    printf("(");
    if(node->key)
        printf("%s", node->key);
    if(node->info)
        printf(", %s", node->info);
    printf(")");
}

int addElement(Tree* tree, KeyType key, InfoType info){
    Node* root = tree->root;
    Node* ptr = root;
    Node* par = NULL;
    if(root == NULL){
        root = malloc(sizeof(Node));
        root->info = info;
        root->key = key;
        root->left = NULL;
        root->right = NULL;
        root->par = NULL;
        // printf("Root: (%s, %s)\n", root->info, root->key);
        tree->root = root;
        return 0;
    }

    while(ptr!=NULL) 
    {
        par = ptr;
        if (keyCompare(key, par->key)<0){
            ptr = par->left;
        } else {
            ptr = par->right;
        }
    }

   
    ptr = malloc(sizeof(Node));
    ptr->info = info;
    ptr->key = key;
    ptr->left = NULL;
    ptr->right = NULL;
    ptr->par = par;
    ptr->h = 1;
    if (keyCompare(key, par->key)<0){
        par->left = ptr;
    } else {
        par->right = ptr;
    }
    tree->root = root;
    rebalance(ptr, tree);
    return 0;
}

KeyType readKey(){
    KeyType key = read_line();
    return key;
}

InfoType readInfo(){
    KeyType info = read_line();
    return info;
}

int printTree(Node* root, int step) {
    if(!root) return 1;
    if (root->right) printTree(root->right, step + 9);
    if (step>=5)
    {
        for (int i = 0; i <= step-5; i++)
            printf(" ");
        for (int i = 0; i <= 3; i++)
            printf("-");
    }
    printNode(root);
    printf("\n");
    if (root->left) printTree(root->left, step + 9);
}

Node* findByKey(Node* root, KeyType key, int* k, int number){
    int f = 0;
    Node* res = NULL;
    // printText(root->key);
    if(root && (keyCompare(root->key, key) == 0) )
        f = 1;

    if(f && !res)
    {   
        *k +=1;
        if (*k==number)
        {
            // printf("%d: ", *k);
            // printNode(root);
            return root;
        }
        
    }

    if(root->right &&  (keyCompare(root->key, key) <= 0) )
    {
        res = findByKey(root->right, key, k, number);
    }

    

    if(root->left && (keyCompare(root->key, key) >= 0) && !res )
    {
        res = findByKey(root->left, key, k, number);
    }
    return res;
}

int treeTraversal(Node* root, KeyType min, KeyType max){
    int f = 0;
    if((keyCompare(root->key, min) >= 0) && (keyCompare(root->key, max) <= 0)  )
        f = 1;

    if(root->right &&  (keyCompare(root->key, max) <= 0))
    {
        treeTraversal(root->right, min, max);
    }

    if(f)
        printNode(root);
    
    if(root->left &&  (keyCompare(root->key, min) >= 0) )
    {
        treeTraversal(root->left, min, max);
    }
}


Node* findMax(Node* root, KeyType max)
{
    int f = 0;
    // printText(root->key);
    

    if(root->right &&  (keyCompare(root->right->key, max) <= 0) )
    {
        return findMax(root->right, max);
    }

    
    if(root && (keyCompare(root->key, max) <= 0) ){
        return root;
    }
    else if(root->left)
    {
        return findMax(root->left, max);
    }
    return NULL;
}


Node* spetialSearch(Node* root, KeyType max, int number){
    Node* res = findMax(root, max);
    if(!res)
        return NULL;
    int k = 0;
    res = findByKey(root, res->key, &k, number);
    return res;
}

int cutNode(Node* node)
{   
    if(!node)
        return 1;
    Node* parent = node->par;
    int side;
    if(parent)
    {
        if(node == parent->left)
            side = 0;
        else
            side = 1;
    }

    if(!(node->left || node->right))
    {
        freeNode(node);
        free(node);
        if(!parent)
            return 0;
        if(side)
            parent->right = NULL;
        else
            parent->left = NULL;
        return 0;
    }

    if(!(node->left && node->right))
    {
        Node* child;
        if(node->left)
            child = node->left;
        else
            child = node->right;
        freeNode(node);

        if(!parent)
        {
            node->info = child->info;
            node->key = child->key;
            child->info = NULL;
            child->key = NULL;
            cutNode(child);
            return 0;
        }

        if(node->left)
        {
            node->left->par = parent;
            if(side)
                parent->right = node->left;
            else
                parent->left = node->left;
        }
        else
        {
            node->right->par = parent;
            if(side)
                parent->right = node->right;
            else
                parent->left = node->right;
        }
        free(node);
        return 0;
    }
    
    printf("You fucked up in cutNode()\n");
    return 1;
}

int deleteNode(Tree* tree, KeyType key, int number)
{
    Node* root = tree->root;
    int k = 0;
    if(!root || !key || number<1)
        return 1;
    Node* targ = findByKey(root, key, &k, number);
    if(!targ)
        return 1;
    if((targ->left && targ->right) == 0)
    {
        cutNode(targ);     
        fullRebalance(tree);
        return 0;
    }

    Node* new = findMax(targ->left, targ->key);
    if(!new)
        printf("LMAO WTF HOW?\n");
    printText(key);
    printNode(new);
    printf("\n");
    // printNode(new);
    freeNode(targ);
    targ->info = new->info;
    targ->key = new->key;
    // printNode(targ);
    new->info = NULL;
    new->key = NULL;
    cutNode(new);
    fullRebalance(tree);
    return 0;

}

int readFromFile(FILE* fb, Tree* tree)
{
    KeyType key = NULL;
    InfoType info = NULL;
    Node new;
    while(!feof(fb))
    {
        key = fread_line(fb);
        info = fread_line(fb);
        // printText(key);
        // printText(info);
        addElement(tree, key, info);
    }
    return 0;
}

int freeTree(Node* root)
{
    if(!root)
        return 1;
    if(root->left)
        freeTree(root->left);
    if(root->right)
        freeTree(root->right);
    freeNode(root);
    free(root);
    return 0;
}


