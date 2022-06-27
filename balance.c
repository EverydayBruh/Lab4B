#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "structs.h"
#include "InOut.h"
#include "timing.h"

int max(int a, int b)
{
    if(a > b)
        return a;
    else    
        return b;
}

int avlheight(Node* node)
{
    if(!node)
        return 0;
    else    
        return node->h;
}

int imbalance(Node* node)
{
    return avlheight(node->right)- avlheight(node->left);
}

int chekDir(Node* child)
{
    if(child->par == NULL)
        printf("ChekDir err empty par");
        return 0;
    if(child == child->par->left)
        return -1;
    else 
        return 1;
}

Node* child(Node* node, int dir)
{
    if(dir < 0)
        return node->left;
    else
        return node->right;
}

void insertChild(Node* root, Node* child, int side)
{
    if(child)
        child->par = root;
    if(side < 0)
        root->left = child;
    else
        root->right = child;
}



void rotate(Node* pivot, int dir, Tree* tree)
{
    // printf("Rotate!\n");
    Node* p = pivot->par;
    Node* g = p->par;

    // printInteger(dir);
    p->h = avlheight(child(pivot, dir)) + 1;
    pivot->h = p->h + 1;
    pivot->par = g;
    if(g == NULL)
        tree->root = pivot;
    else if(g->left == p)
        g->left = pivot;
    else 
        g->right = pivot;
    
    Node* c = child(pivot, dir);
    insertChild(p, c, -dir);
    insertChild(pivot, p, dir);
    
    // printf("Still alive\n");
    
}

void doubleRotate(Node* pivot, int dir, Tree* tree)
{
    // printf("Double rotate\n");
    Node* n = pivot->par;
    Node* p = n->par;
    Node* g = p->par;
    pivot->h = n->h;
    n->h = p->h = pivot->h - 1;
    pivot->par = g;
    if(!g)
        tree->root = pivot;
    else    
        if (g->left == p)
            g->left = pivot;
        else 
            g->right = pivot;
    
    Node* t2 = child(pivot, - dir);
    Node* t3 = child(pivot, dir);

    insertChild(n, t2, dir);
    insertChild(pivot, n, -dir);

    insertChild(p, t3, -dir);
    insertChild(pivot, p, dir);
        

}

int rebalance(Node* start, Tree* tree){
    if(!start)
        return 1;
    // printf("Rebalance!\n");
    // printTree(tree->root, 0);
    Node* node = start->par;
    int skew = imbalance(node);
    while(abs(skew) == 1)
    {
        node->h = max(avlheight(node->left), avlheight(node->right)) + 1;
        node = node->par;
        if(!node)
            return 1;
        skew = imbalance(node);
    }
    // printf("Still alive 1\n");
    if(skew != 0)
    {
        int dir = -skew / 2;
        Node* n = child(node, -dir);
        // printf("Child: "); printNode(n); printf("\n");
        int prev_scew = imbalance(n);
        if (prev_scew == dir)
            doubleRotate(child(n, dir), dir, tree);
        else
            rotate(n, dir, tree);
    }
    return 0;
}

int fullRebalance(Tree* tree){
    Node* node = tree->root;
    if(!node)
        return 1;
    Node* par;
    while (node->h > 1)
    {
        par = node->par;
        if(avlheight(node->left) > avlheight(node->right))
            node = node->left;
        else
            node = node->right;
    }
    rebalance(node, tree);
    return 0;
    
}