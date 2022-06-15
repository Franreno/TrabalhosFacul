/**
 * Francisco Reis Nogueira
 * 11954374
 */

#include "dining.h"

void *DiningPhil(void *num)
{
    while (1)
    {
        int *i = num;

        sleep(1);
        printf("O filosofo %d esta pensando\n", *i);
        pegarGarfo(*i);
        printf("O filosofo %d esta comendo\n", *i);
        sleep(1);
        deixarGarfo(*i);
    }
}

int main()
{
    int filosofos[5];
    pthread_t threads[5];

    inicializar();

    for(int i=0; i<5; i++)
    {
        filosofos[i] = i;
        pthread_create(&threads[i], NULL, DiningPhil, &filosofos[i]);
        printf("O filosofo %d esta pensando\n", i+1);
    }

    for(int i=0; i<5; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}