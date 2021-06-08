#include "quicksort.h"

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

int checkForDuplicates(list *aux, elem randomNumber)
{
    for(int i=0; i<TAM; i++)
    {
        if(aux->elements[i] == randomNumber)
        {
            // printf("%d == %d\n" , aux->elements[i] , randomNumber);
            return 0;
        }
    }

    return 1;
}



void insertUniqueElements(list *l)
{
    //Create an auxilary array to store already used elements.
    list aux;
    create(&aux);
    aux.elements[0] = 1;

    for(int i=0; i< TAM; i++)
    {
        //Get a random number
        int flag = 0;
        while(!flag)
        {
            elem randomNumber = rand()%TAM;
            //check if aux has the number
            flag = checkForDuplicates(&aux, randomNumber);
            
            if(flag == 1) //randomNumber isnt in the array
            {
                insert(l , randomNumber);
                insert(&aux, randomNumber);
            }

            if(aux.listSize >= TAM-1)
                break;

        }

    }
}