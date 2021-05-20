/*
Nome: Francisco Reis Nogueira
Exercicio:
    Problema da maior soma de subsequencia em um array
    [-2,11,-4,13,-5,-2] -> maior soma: 20 (11 + (-4) + 13)
    Implementar um programa para resolver o problema e analise-o
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Implementacao estatica
#define TAM 1000000
#define repeticoes 10 // Fazer varias vezes e tirar a media

void writeOutput(int i, double somaTempo)
{
    FILE *fd;
    fd = fopen("out.txt" , "a");
    fprintf(fd, "%d %0.10f\n" , i, somaTempo);
    fclose(fd);
}


int maiorSubsequenciaN3(int vet[], int size)
{
    int soma, maiorSoma = 0;
    for (int i=0; i<size; i++) //inicio subsequencia
    {
        for(int j=0; j<size; j++) //final subsequencia
        {
            soma = 0;
            for(int k=i; k<=j; k++)
                soma += vet[k];
            if(soma > maiorSoma)
                maiorSoma = soma;
        }
    }
    return maiorSoma;
}

int maiorSubsequenciaN2(int vet[], int tam)
{
    int soma, maiorSoma = 0;
    for (int i=0; i<tam; i++)
    {
        soma = 0;
        for(int j=i; j<tam; j++)
        {
            soma += vet[j];
            if(soma > maiorSoma)    
                maiorSoma = soma;
        }
    }
    return maiorSoma;
}

int maiorSubsequenciaNLogNRecursive(int vet[], int ini, int fim)
{
    int maiorEsq, maiorDir, maiorAmbos; //maior soma de subsequencia do lado esquerdo, direito e soma dos valores
    int meio, soma, maiorSomaParcialEsq, maiorSomaParcialDir;

    if(ini == fim)
        return(vet[ini] < 0) ? 0 : vet[ini]; //vetor unitario, criterio de parada. Se o termo for zero, retorna zero, senao retorna o valor do vetor


    //processar recursivamente e independentemente a metade inferior e metade superior
    meio = ini + (fim-ini) / 2;
    maiorEsq = maiorSubsequenciaNLogNRecursive(vet, ini, meio);
    maiorDir = maiorSubsequenciaNLogNRecursive(vet, meio+1, fim);

    // descobrir maior subsequencia que termina no meio
    soma = maiorSomaParcialEsq = 0;
    for (int i = meio; i>=ini; i--)
    {
        soma += vet[i];
        if (soma > maiorSomaParcialEsq)
            maiorSomaParcialEsq = soma;
    }

    soma = maiorSomaParcialDir = 0;
    for (int i = (meio+1) ; i<=fim; i++)
    {
        soma += vet[i];
        if (soma > maiorSomaParcialDir)
            maiorSomaParcialEsq = soma;
    }

    maiorAmbos = maiorSomaParcialDir + maiorSomaParcialEsq;

    if(maiorEsq > maiorDir)
        return (maiorDir > maiorEsq) ? maiorEsq : maiorAmbos;
    else
        return (maiorDir > maiorAmbos) ? maiorDir : maiorAmbos;

}


int maiorSubsequenciaNLogN(int vet[], int tam)
{

    return maiorSubsequenciaNLogNRecursive(vet, 0, tam-1);
}

int maiorSubsequenciaN(int vet[], int tam)
{
    int soma = 0, maiorSoma = 0;
    for(int i=0; i<tam; i++)
    {
        soma += vet[i];
        if (soma > maiorSoma)
            maiorSoma = soma;
        else
            if(soma < 0)
                soma = 0;
    }
    return maiorSoma;
}


int main()
{
    //int vet[TAM] ={-2,11-4,13,-5,-2};
    //printf("Maior subsequencia: %d\n" , maiorSubsequenciaN3(vet, 6) );

    clock_t tempoIni,timeEnd;
    double somaTempo = 0;
    int vet[TAM];

    FILE *fd;
    fd = fopen("out.txt" , "w");
    fclose(fd); 

    for(int i=100000; i<TAM; i+=10000) // Tamanhos cada vez maiores do vetor
    {
        somaTempo = 0;
        for(int j=0; j<=repeticoes; j++) // repete varias vezes para obter tempo medio
        {
            for(int k=0; k<i; k++)
            {
                vet[k] = rand()%TAM;
                if(vet[k]%2)
                    vet[k] *= -1;
            }
            tempoIni = clock();
            maiorSubsequenciaNLogN(vet, i);
            timeEnd = clock();
            somaTempo += ( (double) (timeEnd - tempoIni)/CLOCKS_PER_SEC );
        }
        //exibir tempo medio
        printf("%d %0.10f\n" , i, somaTempo / (double) repeticoes);
        writeOutput(i, somaTempo/(double)repeticoes);
    }

}
