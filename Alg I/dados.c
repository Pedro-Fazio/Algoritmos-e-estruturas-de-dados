#include "dados.h"

void Pilha_Inicia(PilhaEstat *p) {
    p->topo = -1;
}

int Pilha_Vazia(PilhaEstat p) {
    if(p.topo == -1)
        return 1;
    else 
        return 0;
}

int Pilha_Cheia(PilhaEstat p) {
    if(p.topo == max - 1)
        return 1;
    else 
        return 0;
}

int Pilha_Insere(PilhaEstat *p, int x) {
    if(Pilha_Cheia(*p))
        return 1;
    
    p->topo++;
    p->item[p->topo] = x;
    //p->item[p->topo++] = x;
    return 0;
}

int Pilha_Remove(PilhaEstat *p) {
    int aux;
    
    if(Pilha_Vazia(*p))
        printf("A pilha está vazia!");

    aux = p->item[p->topo];
    p->topo--;

    return aux;
    
}