#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <stdbool.h>

typedef enum{
    NODE_RED,
    NODE_BLACK
}NodeColor ;

struct _no{
    int data;
    NodeColor color;
    struct _no* left;
    struct _no* right;
    struct _no* parent;

};

typedef struct _no TNo;
typedef struct _redblacktree RedBlackTree;
struct _redblacktree{
    TNo* root;
    TNo* nil;
};

RedBlackTree* RbTree_creat();
bool RbTree_insert(RedBlackTree*, int);
void RbTree_PrintLevel(RedBlackTree*);

#endif