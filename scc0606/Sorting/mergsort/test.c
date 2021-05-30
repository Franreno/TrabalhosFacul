#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define TAM 1000
#define repetition 10

void merge(int vetor[], int comeco, int meio, int fim) {
    int com1 = comeco, com2 = meio+1, comAux = 0, tam = fim-comeco+1;
    int *vetAux;
    vetAux = (int*)malloc(tam * sizeof(int));

    while(com1 <= meio && com2 <= fim){
        if(vetor[com1] < vetor[com2]) {
            vetAux[comAux] = vetor[com1];
            com1++;
        } else {
            vetAux[comAux] = vetor[com2];
            com2++;
        }
        comAux++;
    }

    while(com1 <= meio){  //Caso ainda haja elementos na primeira metade
        vetAux[comAux] = vetor[com1];
        comAux++;
        com1++;
    }

    while(com2 <= fim) {   //Caso ainda haja elementos na segunda metade
        vetAux[comAux] = vetor[com2];
        comAux++;
        com2++;
    }

    for(comAux = comeco; comAux <= fim; comAux++){    //Move os elementos de volta para o vetor original
        vetor[comAux] = vetAux[comAux-comeco];
    }
    
    free(vetAux);
}

void mergeSort(int vetor[], int comeco, int fim){
    if (comeco < fim) {
        int meio = (fim+comeco)/2;

        mergeSort(vetor, comeco, meio);
        mergeSort(vetor, meio+1, fim);
        merge(vetor, comeco, meio, fim);
    }
}

int createArray(int **vet)
{
    int* vetAux = (int*)malloc(TAM*sizeof(int));
    memset(vetAux,0,sizeof(int));



    for(int i=0; i<TAM; i++)
    {
        int flag = 0;
        while(!flag)
        {
            int randNumber = rand()%TAM;
            //search for the randNumber if it already exists in the auxilary array
            for(int j=0; j<TAM; j++)
            {
                if(vetAux[j] == randNumber)
                    break;
                else if(j==TAM-1)
                {
                    for(int k=0; k<TAM; k++)
                    {
                        if(vetAux[k] == 0)
                            vetAux[k] = randNumber;
                    }
                    flag = 1;
                }
            }

            for(int j=0; j<TAM; j++)
            {
                if(*(vet)[j] != 0)
                    *(vet)[j] = randNumber;
            }
            
        }

    }
}



int main()
{
    int* vet = (int*)malloc(sizeof(int)*TAM);
    memset(vet,0,sizeof(int));
    createArray(&vet);

    for(int i=0; i<TAM; i++)
        printf("%d " , vet[i]);

    printf("\n");

    //Create array
    // int vet[10] = {9,2,3,1,4,5,7,6,8,0};
    // mergeSort(vet, 0, 9);
    // for(int i=0; i<10; i++)
    //     printf("%d " , vet[i]);

    // printf("\n");
    return 0;
}