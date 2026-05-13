#include <stdio.h>
#include <stdlib.h>
#include "BinTree.h"
#include <stdbool.h>
#include "RedBlackTree.h"



int main(){

    RedBlackTree* tree_ed22 = RbTree_creat();

    int vetor[5];
    vetor[0] = 10;
    vetor[1] = 5;
    vetor[2] = 3;
    vetor[3] = 8;
    vetor[4] = 15;

  for (int i = 0; i < 5; i++){
    if (!RbTree_insert(tree_ed22, vetor[i])){
        printf("Erro ao inserir elemento %d na árvore", vetor[i]);
    }
  }
  RbTree_PrintLevel(tree_ed22);
  
}