#include "BinTree.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct _no{
    int key;
    TNo* parent;
    TNo* right;
    TNo* left;
    int altura;
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
        new->altura = 1;
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

    else if (ante->key > new->key){
        ante->left = new;
    }
    else{
        ante->right = new;
    }

    return true;
};

void BT_pre(TNo* root){
    if(!root) return;

    printf("[%d] ", root->key);
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
    printf("[%d] ", root->key);
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
    printf("[%d] ", root->key);
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


TNo* BT_sucessor_sem_pai(TNo* root, TNo* target){
    if(!root || !target) return NULL;

    if (root->right){
        return BT_min(root->right);
    }

    TNo* current = root;
    TNo* sucessor = NULL;
    while (current != NULL){
        if (current->key > target->key){
            sucessor = current;
            current = current->left;
        }
        else if(current->key < target->key){
            current->right;
        }
        else{
            break;
        }
        
    }

    return sucessor;
    

}





//coloca o no2 como root caso NULL(if)
//coloca como filho a esquerda (else if)
//coloca como filho a direira(else)
//coloca o parente no1 como parente nó 2
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


void BT_printf_linha(TNo* root){
    if(!root) return;

    TNo* fila[1000];
    int inicio = 0;
    int fim = 0;

    fila[fim++] = root;

    while(inicio < fim){
        int tamanho_nivel = fim - inicio;

        for (int i = 0; i < tamanho_nivel; i++){
            TNo* atual = fila[inicio++];
            printf("%d ", atual->key);

            if(atual->left != NULL) fila[fim++] = atual->left;
            if(atual->right != NULL) fila[fim++] = atual->right;
        }
        printf("\n");
    }
    
}

int BT_altura(TNo* root){
    if(!root) return -1;

    int altDir = BT_altura(root->right);
    int altEsq = BT_altura(root->left);

    if (altDir > altEsq){
        return altDir + 1;
    }
    else {
        return altEsq + 1;
    }
    
}

int altura(TNo* root){
    if(!root) return 0;
    return root->altura;
}

int maior(int a, int b){
    return (a>b) ? a:b;
}

TNo* rotacaoEsquerda(TNo* root){
    TNo* y = root->right;
    TNo* T2 = y->left;

    y->left = root;
    root->right = T2;

    root-> altura = maior(altura(root->right), altura(root->left));
    y-> altura = maior(altura(y->right), altura(y->left));

    return root;
}

TNo* rotacaoDireita(TNo* root){
    TNo* y = root->left;
    TNo* T2 = y->right;

    y->right = root;
    root->left = T2;

    root->altura = maior(altura(root->right), altura(root->left));
    y->altura = maior(altura(y->right), altura(root->left));

    return y;
}

TNo* rotacaoDuplaDireita(TNo* root){
    root->left = rotaçaoEsquerda(root->left);
    return rotaçaoDireita(root);
}

TNo* rotacaoDuplaEsquerda(TNo* root){
    root->right = rotaçaoDireita(root->right);
    return rotacaoEsquerda(root);
}

bool AVLT_insert(BinTree* tree, int info){
    if(!tree) return false;

    TNo* new = TNo_createFill(info);
    if(new){
        TNo* current = tree->root;
        TNo* ante = NULL;

        while (current != NULL){
            ante = current;
            if (new->key > current->key){
                current = current->right;
            }
            else if(current->key > new->key){
                current = current->left;
            }
            else{
                return false;
            }
        }
         new->parent = ante;

        if (!ante){
            tree->root = new;
        }

        else if (ante->key > new->key){
            ante->left = new;
        }
        else{
            ante->right = new;
        }

        int alt_dir = (ante->right == NULL) ? 0 : ante->right->altura;
        int alt_esq = (ante->left == NULL) ? 0 : ante->left->altura;

        ante->altura = (alt_dir > alt_esq) ? alt_dir+1 : alt_esq+1;
        

        int fb = alt_dir - alt_esq;

        if (fb == -2){

            int fb_filho = altura(ante->left->right) - altura(ante->left->left);

            if (fb_filho <= 0){
                ante = rotacaoDireita(ante);
            }
            else{
                ante = rotacaoDuplaDireita(ante);
            }
        }
        if (fb == 2){

            int fb_filho = altura(ante->right->right) - altura(ante->right->left);

            if (fb_filho >= 0){
                ante = rotacaoEsquerda(ante);
            }
            else{
                ante = rotacaoDuplaEsquerda(ante);
            }
            
        }
        return true;
    }
    return false;
}