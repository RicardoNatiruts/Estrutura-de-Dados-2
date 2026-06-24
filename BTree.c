#include "Btree.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define termo 3
#define max (termo*2) - 1
#define min (termo - 1)

typedef struct _no{
    int chaves[(2*termo)-1];
    struct _no* ponter[2*termo];
    int qtd;
    bool folha;
}BNo;

typedef struct _bTree{
    BNo* raiz;
}BTree;


BNo* BTree_noCreate(){
    BNo* novo = malloc(sizeof(BNo));
    if (novo){
        novo->qtd = 0;
        novo->folha = true;
        
        for (int i = 0; i < 2*termo; i++){
            novo->ponter[i] = NULL;
        }
        
    }
    return novo;
}

BTree* BTree_create(){
    BTree* novo = malloc(sizeof(BTree));
    if (novo){
        novo->raiz = BTree_noCreate(); 
    }
    return novo;
}

bool BTree_split(BNo* raiz, int indice){
    if(!raiz || !raiz->ponter[indice]) return false;

    BNo* dir = BTree_noCreate();

    int mediana = raiz->ponter[indice]->chaves[termo - 1];

    dir->ponter[0] = raiz->ponter[indice]->ponter[termo];
    for (int i = termo; i < max; i++){
        dir->chaves[i - termo] = raiz->ponter[indice]->chaves[i];
        dir->ponter[i - termo + 1] = raiz->ponter[indice]->ponter[i+1];
    }
    dir->folha = raiz->ponter[indice]->folha;
    dir->qtd = min;
    raiz->ponter[indice]->qtd = min;

    for (int i = raiz->qtd; i > indice; i--){
        raiz->ponter[i + 1] = raiz->ponter[i];
    }
    raiz->ponter[indice + 1] = dir;

    for (int i = raiz->qtd - 1; i >= indice; i--){
        raiz->chaves[i+1] = raiz->chaves[i];
    }
    raiz->chaves[indice] = mediana;
    raiz->qtd++;
    
    return true;
}

bool BTree_insert_noFull(BNo* raiz, int chave){
    int i = raiz->qtd-1;
    if (raiz->folha){
        while(i >= 0 && raiz->chaves[i] > chave){
            raiz->chaves[i + 1] = raiz->chaves[i];
            i--;
        }
        raiz->chaves[i + 1] = chave;
        raiz->qtd++;
        return true;

    }
    else{
        while (i >= 0 && raiz->chaves[i] > chave){
            i--;
        }
        i++;
        
        
        if(raiz->ponter[i]->qtd == max){
            BTree_split(raiz, i);
            if(raiz->chaves[i] < chave){
                i++;
            }
        }
        return BTree_insert_noFull(raiz->ponter[i], chave);
    }
    
}

bool BTree_insert(BTree* arvore, int chave){
    BNo* raiz = arvore->raiz;
    if(raiz->qtd == max){
        BNo* current = BTree_noCreate();
        arvore->raiz = current;
        current->folha = false;
        current->ponter[0] = raiz;
        BTree_split(current, 0);
        return BTree_insert_noFull(current, chave);
    }
    else return BTree_insert_noFull(raiz, chave);
}