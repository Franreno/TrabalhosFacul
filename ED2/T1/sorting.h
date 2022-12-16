/*
    Francisco Reis Nogueira - 11954374
    Joao Augusto Fernandes Barbosa - 11953348
    Vinicius Cubi Santos Paulo -11965693
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

/*
    Mudar aqui os valores maximos para cada metodo
*/
#define TAM_BUBBLE 10000
#define TAM_BUBBLEOT 100000
#define TAM_QUICK 1000000
#define TAM_RADIX 1000000
#define TAM_HEAP 1000000

#define Repeticoes 10

#define Aleatorio 1
#define Ordenado  2
#define Invertido 3

typedef int elem;

typedef struct lista
{
    elem *elements;
    long tamanho;
}lista;

/*---------------------------------------*/
void criaLista(lista *l, long TAM_MAX);
void apagaLista(lista *l);
int insereLista(lista *l, elem e, long TAM_MAX);
void printLista(lista *l);
void insereAleatorio(lista *l, long TAM_MAX);
void insereOrdenado(lista *l, long TAM_MAX);
void insereInvertido(lista *l, long TAM_MAX);
void insereMetodoCriacao(lista *l, long TAM_MAX, int metodoCriacao);

/*---------------------------------------*/
void calculaEmpirico(int tipo, int tipoCriacao);
double calculaMedia(double *vec);
double calculaDesvioPadrao(double *vec, double media);
void realizaMetodoOrdenacao(lista *l, int metodo);

/*---------------------------------------*/
void bubbleSort(lista *l);
void bubbleSortAprimorado(lista *l);

/*---------------------------------------*/
void quickSort(lista *l, long inicio, long fim);
long Random_partition(lista *l, long inicio, long fim);
long Partition(lista *l, long inicio, long fim);

/*---------------------------------------*/
int radixSort(lista *l);
int countingSort(lista *l, long size, long pos);
elem maiorNum(lista *l, long size);

/*---------------------------------------*/
void heapSort(lista *l, long n);
void Heapify(lista *l, long n, long i);