//gcc mutations -o mutations.c -march=native -O3
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define maxLimit 1000
#define tamPop 10
#define taxMut 2
#define GOAL 500

typedef struct org
{

    struct pops
    {
        double ind[tamPop];
        double indTemp[tamPop];
        double fit[tamPop];
    } pops;

    struct params
    {
        double maxfit;
        double media;
        int gen;
    } params;

} org;

typedef struct org Org;

void initPop(Org *d)
{
    d->params.gen = 0;
    d->params.maxfit = 0.0;
    d->params.media = 0.0;

    for (int i = 0; i < tamPop; i++)
    {
        d->pops.ind[i] = (double)(rand() % maxLimit);
    }
}

void printPops(Org *d)
{
    for (int i = 0; i < tamPop; i++)
    {
        printf("\tPop[%d] = %lf\n", i, d->pops.ind[i]);
    }
}

void elitismo(Org *d)
{
    d->params.maxfit = d->pops.fit[0];
    int maxi = 0;

    //Procura pelo melhor
    for (int i = 0; i < tamPop; i++)
    {
        if (d->pops.fit[i] > d->params.maxfit)
        {
            d->params.maxfit = d->pops.fit[i];
            maxi = i;
        }
    }

    for (int i = 0; i < tamPop; i++)
    {
        if (i == maxi)
            continue;

        //Crossover
        d->pops.ind[i] = (d->pops.ind[i] + d->pops.ind[maxi]) / 2.0;

        //Mutacao
        d->pops.ind[i] += ((double)(rand() % maxLimit) - maxLimit / 2) * taxMut / 100.0f;

        if (d->pops.ind[i] > maxLimit)
            d->pops.ind[i] = maxLimit;

        if (d->pops.ind[i] < 0)
            d->pops.ind[i] *= -1.0;
    }
}

void avalia(Org *d)
{
    double x;
    // printf("Generation: %d\n", d->params.gen);
    for (int i = 0; i < tamPop; i++)
    {
        x = d->pops.ind[i];
        float y = x;
        if (x > 500)
            y = 1000 - x;

        d->pops.fit[i] = y;
        d->params.media += y;
        // printf("\tFitness %d (%lf) = %lf\n", i, d->pops.ind[i], d->pops.fit[i]);
    }
    d->params.media/tamPop*1.0;
    for(int i = 0; i<tamPop; i++)
    {
        printf("%d;%lf;%lf\n", d->params.gen, d->pops.ind[i], d->pops.fit[i]);
    }
}

int main()
{
    srand(time(NULL));

    printf("Creating population\n");

    Org allData;
    initPop(&allData);
    printf("Sucess\n");

    while (fabs(allData.params.maxfit - GOAL) > 0.001)
    {

        elitismo(&allData);
        avalia(&allData);
        
        allData.params.gen++;
    }

    return 0;
}