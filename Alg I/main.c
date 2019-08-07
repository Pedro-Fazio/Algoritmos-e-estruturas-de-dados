#include "dados.h"

int main() {
    int aux;
    PilhaEstat *p = malloc(sizeof(p));

    Pilha_Inicia(p);

    Pilha_Insere(p, 8);
    Pilha_Insere(p, 1);
    Pilha_Insere(p, 2);
    Pilha_Insere(p, 3);
    Pilha_Insere(p, 10);

    aux = Pilha_Remove(p);
    printf("%d", aux);
    aux = Pilha_Remove(p);
    printf("%d", aux);
    aux = Pilha_Remove(p);
    printf("%d", aux);
    aux = Pilha_Remove(p);
    printf("%d", aux);
    aux = Pilha_Remove(p);
    printf("%d", aux);

    return 0;
}