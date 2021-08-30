#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include <string.h>

#define maxx 1000
#define TamPop 10
float TaxMut = 2; // 10 = 10%

double ind[TamPop + 1];     //cromossomo dos individuos
double indtemp[TamPop + 1]; //vetor para armazenar os individuos temporariamente para o torneio de 2
double fit[TamPop + 1];
//double bestfit[]
double maxfit = 0.0;
double media = 0.0;
int i, maxi = 0;
int gen = 0;

void avalia()
{
    float x;
    printf("Generation %d\n", gen);
    for (i = 1; i <= TamPop; i++)
    {
        x = ind[i];
        //------- Função doida -------//
        float y = (2 * cos(0.039 * x) + 5 * sin(0.05 * x) + 0.5 * cos(0.01 * x) + 10 * sin(0.07 * x) + 5 * sin(0.1 * x) + 5 * sin(0.035 * x)) * 10 + 500;
        //------ Montanha -------//
        //float y = x;
        //if(x>500)
        //	y=1000-x;
        fit[i] = y;
        printf("\tFitness %d (%f)= %f\n", i, ind[i], fit[i]);
    }
}

void initpop()
{
    for (i = 1; i <= TamPop; i++)
    { // nr entre -10 e +10 -> rand() %20 - 10;
        ind[i] = (double)(rand() % maxx);
    }
}

void elitismo() // Melhor transa com todos
{
    maxfit = fit[1];
    maxi = 1;

    for (i = 2; i <= TamPop; i++) // Busca pelo melhor individuo
    {
        if (fit[i] > maxfit)
        {
            maxfit = fit[i];
            maxi = i;
        }
    }

    for (i = 1; i <= TamPop; i++)
    {
        if (i == maxi) // Protege o melhor individuo
            continue;

        // Crossover
        ind[i] = (ind[i] + ind[maxi]) / 2.0;

        // Mutacao                    | nr = 0-40 |    - 20    |  0,02  |  10%
        ind[i] = ind[i] + ((double)(rand() % maxx) - maxx / 2) * TaxMut / 100.0f;
        if (ind[i] > maxx)
            ind[i] = maxx;
        if (ind[i] < 0)
            ind[i] = ind[i] * -1.0;
    }
}

void torneio() // Torneio de 2
{
    int a, b, pai1, pai2;
    maxfit = fit[1];
    maxi = 1;
    for (i = 2; i <= TamPop; i++) // Busca pelo melhor individuo para protege-lo
    {
        if (fit[i] > maxfit)
        {
            maxfit = fit[i];
            maxi = i;
        }
    }

    for (i = 1; i <= TamPop; i++)
        indtemp[i] = ind[i]; // Backup dos individuos

    // Torneio
    for (i = 1; i <= TamPop; i++)
    {
        if (i == maxi) // Protege o melhor individuo
            continue;

        // Sorteia dois individuos para 1ro torneio
        a = (rand() % TamPop) + 1;
        b = (rand() % TamPop) + 1;
        if (fit[a] > fit[b])
            pai1 = a;
        else
            pai1 = b;

        // Sorteia mais dois individuos para 2do torneio
        a = (rand() % TamPop) + 1;
        b = (rand() % TamPop) + 1;
        if (fit[a] > fit[b])
            pai2 = a;
        else
            pai2 = b;

        // Crossover
        ind[i] = (indtemp[pai1] + indtemp[pai2]) / 2.0; // Pegar os pais antigos, pois posso sortear os novos filhos que foram alterados

        // Mutacao                    | nr = 0-40 |    - 20    |  0,02  |  10%
        ind[i] = ind[i] + (double)(((rand() % maxx - (maxx / 2.0)) / 100.0) * TaxMut);
    }
}

//just explain the commands
void ag()
{

    elitismo(); // Seleciona o melhor individuo para transar com todos e Faz Crossover e Mutacao e ja' substitui na Populacao
    avalia();   // Avalia os individuos da Populacao

    //torneio();    // FAz torneio de 2 entre os individuos, e Faz Crossover e Mutacao e ja' substitui na Populacao

    // Final do Algoritmo Evolutivo
    gen++;
}

int main(int argc, char *argv[])
{

    srand(time(NULL));

    initpop();
    for(int i=0; i<10000; i++)
        ag();   

    return 0;
}
