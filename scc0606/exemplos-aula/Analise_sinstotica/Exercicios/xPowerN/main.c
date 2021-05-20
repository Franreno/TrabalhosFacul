#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 1000000
#define repeticoes 10

long exponenciacaoN(int x, int n)
{
    long res = 1;
    for(int i=0; i<n; i++)
        res *= x;
    return res;
}


int main()
{
    // int x = 3;
    // int n = 20;
    // long res = exponenciacaoN(x, n);
    // printf("O valor de %d elevado a %d eh: %ld\n" , x, n, res);

    double somaTempo;
    clock_t tempoIni, tempoFim;

    int x = 2;
    for(int i=100000; i<TAM; i+=10000)
    {
        for (int j=0; j<repeticoes; j++)
        {
            tempoIni = clock();
            exponenciacaoN(x,i);
            tempoFim = clock();

            somaTempo += (double)(tempoFim-tempoIni) / CLOCKS_PER_SEC;
        }

        printf("%d %0.15lf\n" , i , somaTempo / (double) repeticoes);
    }
}