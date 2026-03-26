#ifndef BINTREE_H
#define BINTREE_H

#include <stdbool.h>

typedef struct __binTree BinTree;

BinTree* BT_create();

bool BT_insert(BinTree*, int);
void BT_pre(TNo*);
void BT_in(TNo*);
void BT_pos(TNo*);
TNo* BT_search(TNo*, int);
TNo* BT_max(TNo*);
TNo* BT_min(TNo*);
TNo* BT_sucessor(TNo*);

#endif