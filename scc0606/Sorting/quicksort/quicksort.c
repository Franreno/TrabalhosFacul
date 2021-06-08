#include "quicksort.h"

int main()
{
    list l;
    clock_t startTime, endTime;


    create(&l);
    insertUniqueElements(&l);
    printList(&l);



    // double sumTime = 0;
    // for (int i=0; i < repeticoes; i++)
    // {
    //     create(&l);

    //     for(long j=0; j<TAM; j++)
    //         insert(&l, rand()%TAM);


    //     // printList(&l);

    //     startTime = clock();
    //     sortQuickSort(&l);
    //     endTime = clock();

    //     // printList(&l);

    //     sumTime += (double)(endTime - startTime);
        
    //     destroy(&l);
    // }

    // printf("Tempo total: %0.10f\n" , (sumTime / (double) repeticoes / CLOCKS_PER_SEC) );

    return 0;
}

void sortQuickSort(list *l)
{

}