/*
    1,3,2,5,4 -> 
    [1],3,2,5,4 -> compara 1 com 3 (1 < 3) ? True. Contiue
    1,[3],2,5,4 -> compara 3 com 2 (3 < 2) ? False. Troca eles
    1,2,[3],5,4 -> compara 3 com 5 (3 < 5) ? True. Continue
    1,2,3,[5],4 -> compara 5 com 4 (5 < 3) ? False. Troca eles.
    1,2,3,4,[5] -> ordenado.
*/

#include "bubble.h"


int main()
{
    list l;
    clock_t startTime, endTime;


    double sumTime = 0;
    for (int i=0; i < repeticoes; i++)
    {
        create(&l);

        for(long j=0; j<TAM; j++)
            insert(&l, rand()%TAM);


        // printList(&l);

        startTime = clock();
        sortBubbleSort(&l);
        endTime = clock();

        // printList(&l);

        sumTime += (double)(endTime - startTime);
        
        destroy(&l);
    }

    printf("Tempo total: %0.10f\n" , (sumTime / (double) repeticoes / CLOCKS_PER_SEC) );

    return 0;
}

void sortBubbleSort(list *l)
{
    int continue_ = 1; // true
    int iteration = 1;
    elem aux;
    while( continue_ )
    {
        continue_ = 0;
        for (long i=0; i< l->listSize-iteration; i++)
        {
            if (l->elements[i] > l->elements[i+1])
            {
                aux = l->elements[i];
                l->elements[i] = l->elements[i+1];
                l->elements[i+1] = aux;
                continue_ = 1;
            }
        }
        iteration++;
    }
}