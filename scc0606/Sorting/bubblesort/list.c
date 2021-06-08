#include "bubble.h"

void create(list *l) {
    l->listSize = 0;
    l->elements = malloc(sizeof(elem)*TAM);
    l->copy = malloc(sizeof(elem)*TAM);
    return;
}

void destroy(list *l) {
    free(l->elements);
    free(l->copy);
    l->listSize = 0;
}

int insert(list *l, elem e) {
    if (l->listSize == TAM)
        return 1; // erro, list cheia
    l->elements[l->listSize] = e;
    l->listSize++;
    return 0; // sucesso
}

void printList(list *l) {
    long i = 0;
    if (l->listSize == 0) 
        printf("( )\n");
    else {
        printf("(");
        for (; i < l->listSize-1; i++)
            printf("%d, ", l->elements[i]);
        printf("%d)\n", l->elements[i]);
    }
}
