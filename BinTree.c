#include "BinTree.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _no{
    int key;
    TNo* parent;
    TNo* right;
    TNo* left;
}TNo;

struct __binTree{
    TNo* root;
};

TNo* TNo_createFill(int info){
    TNo* new = malloc(sizeof(TNo));
    if (new != NULL){
        new->key = info;
        new->left = NULL;
        new->parent = NULL;
        new->right =NULL;
    }
    return new;
};

BinTree* BT_create(){
    BinTree* new = malloc(sizeof(BinTree));
    if(new != NULL){
        new->root = NULL;
    };
    return new;
};

bool BT_insert(BinTree* tree, int info){
    if (!tree) return false;

    TNo* new = TNo_createFill(info);
    if (!new)return false;
    

    TNo* ante = NULL;
    TNo* current = tree->root;

    while (current != NULL){
        ante = current;
        if (current->key < new->key){
            current = current->right;
        }
        else{
            current = current->left;
        }
    }
    new->parent = ante;

    if (!ante){
        tree->root = new;
    }

    if (ante->key > new->key){
        ante->left = new;
    }
    else{
        ante->right = new;
    }

    return true;
};

void BT_pre(TNo* root){
    if(!root) return;

    printf("%d", root->key);
    if (root->left){
        BT_pre(root->left);
    }
    if (root->right){
        BT_pre(root->right);
    }
    return;
};

void BT_in(TNo* root){
    if(!root) return;

    if (root->left){
        BT_in(root->left);
    }
    printf("%d", root->key);
    if (root->right){
        BT_in(root->right);
    }
    return;
};

void BT_pos(TNo* root){
    if(!root) return;

    if (root->left){
        BT_pos(root->left);
    }
    if (root->right){
        BT_pos(root->right);
    }
    printf("%d", root->key);
    return;
};

TNo* BT_search(TNo* root, int info){

    while (root != NULL){
        if (root->key == info){
            break;
        }
        if (root->key > info){
            root = root->left;
        }
        else{
            root = root->right;
        }
    }
    return root;
}

TNo* BT_max(TNo* root){

    while (root != NULL){
        if (root->right == NULL){
            break;
        }
        root = root->right;
    }

    return root;
    
}

TNo* BT_min(TNo* root){

    while (root != NULL){
        if (root->left == NULL){
            break;
        }
        root = root->left;
    }

    return root;
}


TNo* BT_sucessor(TNo* root){
    if(!root) return NULL;

    if (root->right){
        return BT_min(root->right);
    }

    TNo* current = root->parent;

    while (current != NULL && root == current->right){
        root = current;
        current = current->parent;
    };

    return current;
}

void BT_transplant(BinTree* tree, TNo* no1, TNo* no2){
    if (!no1->parent){
        tree->root = no2;
    }
    else if (no1 == no1->parent->left){
        no1->parent->left = no2;
    }
    else{
        no1->parent->right = no2;
    }
    if (no2 != NULL){
        no2->parent = no1->parent;
    }
}

bool BT_remove(BinTree* tree, TNo* no){
    if (!tree || !no) return false;
    
    if (no->left == NULL){
        BT_transplant(tree, no, no->right);
    }
    else if (no->right == NULL){
        BT_transplant(tree, no, no->left);
    }
    else{
        TNo* current = BT_min(no->right);
        if (current->parent != no){
            BT_transplant(tree, current, current->right);
            current->right = no->right;
            current->right->parent = current;
        }
        BT_transplant(tree, no, current);
        current->left = no->left;
        current->left->parent = current;
    }
    free(no);
    return true;
}
