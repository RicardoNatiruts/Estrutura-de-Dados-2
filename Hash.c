#define m 11

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



typedef enum _status{LIVRE, OCUPADO}Status;

typedef struct _no {
    int chave;
    Status status;
}HNo;

typedef struct _hash{
    HNo chaves[m];
}Hash;

Hash* Hash_create(){
    Hash* novo = malloc(sizeof(Hash));
    if (novo){
        for (int i = 0; i < m; i++){
            novo->chaves[i].status = LIVRE;
        }
    }
    return novo;
}

int Hash_indice(int chave){
    return chave%m;
}

int Hash_indice2(int chave){
    return 1 + (chave % (m-1));
}

bool Hash_insert_duple(Hash* tabela, int chave){
    if(!tabela) return false;

    int indice = Hash_indice(chave);
    int i = 0;
    while(tabela->chaves[indice].status == OCUPADO && tabela->chaves[indice].chave != chave && i < m){
        i++;
        indice = (Hash_indice(chave) + (i*Hash_indice2(chave)))%m;
    }

    if(i == m) return false;

    if(tabela->chaves[indice].chave == chave && tabela->chaves[indice].status == OCUPADO) return false;

    tabela->chaves[indice].chave = chave;
    tabela->chaves[indice].status = OCUPADO;
    return true;
}

/*typedef struct _no{
    int chave;
    struct _no* proximo;
}TNo;

typedef struct _hash{
    TNo* ponter[m];
}Hash;

Hash* Hash_create(){
    Hash* novo = malloc(sizeof(Hash));
    if(novo){
        for (int i = 0; i < m; i++){
            novo->ponter[i] = NULL;
        }
    }
    return novo;
}

TNo* TNo_create_inFill(int chave){
    TNo* novo = malloc(sizeof(TNo));
    if(novo){
        novo->chave = chave;
        novo->proximo = NULL;
    }
    return novo;
}

bool Fila_insert(TNo* primeiro, int chave){
    if(!primeiro) return false;

    
    TNo* current = primeiro;
    
    while(current->proximo != NULL){
        if (current->chave == chave) {
            return false; 
        }
        current = current->proximo;
    }
    
    if (current->chave == chave) {
        return false; 
    }
    
    TNo* novo = TNo_create_inFill(chave);
    current->proximo = novo;

    return true;
}

int Hash_indice(int chave){
    return chave%m;
}

bool Hash_insert(Hash* tabela, int chave){
    if(!tabela) return false;

    int indice = Hash_indice(chave);
    
    if(tabela->ponter[indice] == NULL){
        tabela->ponter[indice] = TNo_create_inFill(chave);
    }
    else{
        Fila_insert(tabela->ponter[indice], chave);
    }
    return true;
}
*/

