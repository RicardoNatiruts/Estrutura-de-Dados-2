#include <stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include "RedBlackTree.h"



RedBlackTree* RbTree_creat(){
    RedBlackTree* novo = malloc(sizeof(RedBlackTree));
    if(!novo) return NULL;

    novo->nil = malloc(sizeof(TNo));
    novo->nil->color = NODE_BLACK;
    novo->nil->left = novo->nil;
    novo->nil->right = novo->nil;
    novo->nil->parent = novo->nil;
    novo->root = novo->nil;

    return(novo);
}

TNo* TNo_CreateinFill(int info, RedBlackTree* tree){
    TNo* novo = malloc(sizeof(TNo));
    if(!novo) return NULL;

    novo->right = tree->nil;
    novo->left = tree->nil;
    novo->parent = tree->nil;
    novo->data = info;
    novo->color = NODE_RED;

    return novo;
}


void RbTree_Rotate_Right(RedBlackTree* tree, TNo* no){
    TNo* up = no->left;

    //1. Adoção
    no->left = up->right; //Troca filho

    if (up->right != tree->nil){
        up->right->parent = no; //Troca Pai
    }

    
    //2. Troca de Pai
    up->parent = no->parent;//Troca o Pai

    if (no->parent == tree->nil){// Troca filho, casos: root, right, left;
        tree->root = up;
    }
    else if (no == no->parent->right){
        no->parent->right = up;
    }
    else{
        no->parent->left = up;
    }

    //3. Adoção do no
    no->parent = up;
    up->right = no;

    return;
}

void RbTree_Rotate_Left(RedBlackTree* tree, TNo* no){
    TNo* up = no->right;
    
    no->right = up->left;

    if(up->left != tree->nil){
        up->left->parent = no;
    }

    up->parent = no->parent;
    if (no->parent == tree->nil){
        tree->root = up;
    }
    else if(no == no->parent->right){
        no->parent->right = up;
    }
    else{
        no->parent->left = up;
    }

    no->parent = up;
    up->left = no;

    return;
}



bool RbTree_Insert_Fixup(RedBlackTree* tree, TNo* novo){
    while (novo->parent->color == NODE_RED){
        if (novo->parent == novo->parent->parent->left){
            TNo* tio = novo->parent->parent->right;
            if (tio->color == NODE_RED){
                novo->parent->color = NODE_BLACK;
                tio->color = NODE_BLACK;
                novo->parent->parent->color = NODE_BLACK;
                novo = novo->parent->parent;
            }
            else{
                if (novo == novo->parent->right){
                    novo = novo->parent;
                    RbTree_Rotate_Left(tree, novo);
                }
                novo->parent->color = NODE_BLACK;
                novo->parent->parent->color = NODE_RED;
                RbTree_Rotate_Right(tree, novo->parent->parent);
            }
        }
        else{
            TNo* tio = novo->parent->parent->left;
            if (tio->color == NODE_RED){
                novo->parent->color = NODE_BLACK;
                tio->color = NODE_BLACK;
                novo->parent->parent->color = NODE_RED;
                novo = novo->parent->parent;
            }
            else{
                if(novo == novo->parent->left){
                    novo = novo->parent;
                    RbTree_Rotate_Right(tree, novo);
                }
                novo->parent->color = NODE_BLACK;
                novo->parent->parent->color = NODE_RED;
                RbTree_Rotate_Left(tree, novo->parent->parent);
            }
            
        }
        
    }
    tree->root->color = NODE_BLACK;
    return true;

    
}



bool RbTree_insert(RedBlackTree* tree, int info){
    if(!tree) return false;

    TNo* ante = tree->nil;
    TNo* current = tree->root;
    while (current != tree->nil){
        ante = current;
        if (current->data > info){
            current = current->left;
        }
        else{
            current = current->right;
        }
    }

    TNo* novo = TNo_CreateinFill(info, tree);
    if(!novo) return false;

    novo->parent = ante;

    if (ante == tree->nil){
        tree->root = novo;
    }
    else if(novo->data > ante->data){
        ante->right = novo;
    }
    else{
        ante->left = novo;
    }

    
    return RbTree_Insert_Fixup(tree, novo);
    
}

void RbTree_PrintLevel(RedBlackTree* tree){
    if(!tree || tree->root == tree->nil){
        printf("Árvore Vazia\n");
        return;
    }

    TNo* fila[100];
    int inicio = 0;
    int fim = 0;

    const char* nomeCor[] = {"NODE_RED", "NODE_BLACK"};
    fila[fim++] = tree->root;

    while (inicio < fim){
        int nosNivel = fim - inicio;

        while (nosNivel > 0){
            TNo* atual = fila[inicio++];
            printf("%s(%d) ", nomeCor[atual->color], atual->data);

            if(atual->left != tree->nil){
            fila[fim++] = atual->left;
            }
            if(atual->right != tree->nil){
            fila[fim++] = atual->right;
            }

            nosNivel--;
        }

        printf("\n");   
    }    
}