#include <stdio.h>
#include <stdlib.h>
#define max 100

typedef struct {
    int item[max];
    int topo;
} PilhaEstat;

void Pilha_Inicia(PilhaEstat *p);
int Pilha_Vazia(PilhaEstat p);
int Pilha_Cheia(PilhaEstat p);
int Pilha_Insere(PilhaEstat *p, int x);
int Pilha_Remove(PilhaEstat *p);
