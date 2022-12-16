/*
    Francisco Reis Nogueira - 11954374
    Joao Augusto Fernandes Barbosa - 11953348
    Vinicius Cubi Santos Paulo - 11965693
*/

#include "sorting.h"

/*-------------------------------------------------------------------------------------------------------*/
/*-------------------------------------------Funcoes para o uso da Lista---------------------------------*/
/*
    Funcao de criacao da lista
*/
void criaLista(lista *l, long TAM_MAX)
{
    l->tamanho = 0;
    l->elements = malloc(sizeof(lista) * TAM_MAX);
}

/*
    Funcao que da free na lista.
*/
void apagaLista(lista *l)
{
    free(l->elements);
    l->tamanho = 0;
}

/*
    Funcao que insere os elementos na lista.
*/
int insereLista(lista *l, elem e, long TAM_MAX)
{
    if (l->tamanho == TAM_MAX)

        return 0;
    l->elements[l->tamanho] = e;
    l->tamanho++;

    return 1;
}

/*
    Funcao que imprime os elementos da lista
*/
void printLista(lista *l)
{
    long i = 0;
    if (l->tamanho == 0)
        printf("( )\n");
    else
    {
        printf("(");
        for (; i < l->tamanho - 1; i++)
            printf("%d, ", l->elements[i]);
        printf("%d)\n", l->elements[i]);
    }
}

/*
    Funcao que insere os elementos no vetor de maneira aleatoria
*/
void insereAleatorio(lista *l, long TAM_MAX)
{
    srand(time(NULL));
    for (long i = 0; i < TAM_MAX; i++)
        insereLista(l, rand() % TAM_MAX, TAM_MAX);
}

/*
    Funcao que insere os elementos no vetor de maneira crescente
*/
void insereOrdenado(lista *l, long TAM_MAX)
{
    for (long i = 0; i < TAM_MAX; i++)
    {
        insereLista(l, i, TAM_MAX);
    }
}

/*
    Funcao que insere os elementos no vetor de maneira decrescente
*/
void insereInvertido(lista *l, long TAM_MAX)
{
    for (long i = TAM_MAX - 1; i >= 0; i--)
    {
        insereLista(l, i, TAM_MAX);
    }
}

/*
    Funcao que define o tipo de criacao do vetor
    1 -> Aleatorio
    2 -> Ordenado
    3 -> Invertido
*/
void insereMetodoCriacao(lista *l, long TAM_MAX, int metodoCriacao)
{
    if (metodoCriacao == Aleatorio)
        insereAleatorio(l, TAM_MAX);
    else if (metodoCriacao == Ordenado)
        insereOrdenado(l, TAM_MAX);
    else if (metodoCriacao == Invertido)
        insereInvertido(l, TAM_MAX);
}

/*
    Funcao que realiza a troca de dois elementos em um vetor
*/
void trocaElementos(lista *l, long pre, long pos)
{
    elem auxiliar;
    auxiliar = l->elements[pre];
    l->elements[pre] = l->elements[pos];
    l->elements[pos] = auxiliar;
}

/*------------------------------------------------------------------------------------------------*/
/*-------------------------------------------Funcoes de ordenacao---------------------------------*/

void bubbleSort(lista *l)
{
    for (long i = 0; i < l->tamanho; i++)
    {
        for (long j = 0; j < (l->tamanho - i - 1); j++)
        {
            if (l->elements[j] > l->elements[j + 1])
            {
                //Realizar a troca
                trocaElementos(l, j, (j + 1));
            }
        }
    }
}

void bubbleSortAprimorado(lista *l)
{
    int flag = 1;
    for (long i = 0; i < l->tamanho; i++)
    {
        for (long j = 0; j < (l->tamanho - i - 1); j++)
        {
            if (l->elements[j] > l->elements[j + 1])
            {
                flag = 0;
                trocaElementos(l, j, (j + 1));
            }
        }

        if (flag == 1)
            break;
        flag = 1;
    }
}
/*--------------------------------------------------------------------------------------------------*/
/*-------------------------------------------QuickSort e rotinas -----------------------------------*/

void quickSort(lista *l, long inicio, long fim)
{
    if (inicio < fim)
    {
        int pivo = Random_partition(l, inicio, fim);
        quickSort(l, inicio, pivo - 1);
        quickSort(l, pivo + 1, fim);
    }
}

long Random_partition(lista *l, long inicio, long fim)
{
    srand(time(NULL));
    long k = rand() % (fim + 1 - inicio) + inicio;
    trocaElementos(l, k, fim);
    return Partition(l, inicio, fim);
}

long Partition(lista *l, long inicio, long fim)
{
    int pivo = l->elements[fim];
    int i = inicio - 1;

    for (int j = inicio; j < fim; j++)
    {
        if (l->elements[j] < pivo)
        {
            i = i + 1;
            trocaElementos(l, i, j);
        }
    }
    trocaElementos(l, i + 1, fim);
    return (i + 1);
}
/*-----------------------------------------------------------------------------------------------*/
/*-------------------------------------------HeapSort e rotinas ---------------------------------*/

void heapSort(lista *l, long n)
{
    for (long i = (n / 2) - 1; i >= 0; i--)
    {
        Heapify(l, n, i);
    }

    for (long i = n - 1; i > 0; i--)
    {
        trocaElementos(l, 0, i);
        Heapify(l, i, 0);
    }
}

void Heapify(lista *l, long n, long i)
{
    long maior = i;
    long esquerda = (2 * i) + 1;
    long direita = (2 * i) + 2;

    if (esquerda < n && l->elements[esquerda] > l->elements[maior])
    {
        maior = esquerda;
    }

    if (direita < n && l->elements[direita] > l->elements[maior])
    {
        maior = direita;
    }

    if (maior != i)
    {
        trocaElementos(l, i, maior);
        Heapify(l, n, maior);
    }
}

/*------------------------------------------------------------------------------------------------*/
/*-------------------------------------------RadixSort e rotinas ---------------------------------*/


int radixSort(lista *l)
{
    long size = l->tamanho;
    long maior = maiorNum(l, size);
    long pos = 1;

    while ((maior / pos) > 0)
    {
        countingSort(l, size, pos);
        pos = pos * 10;
    }

    return 1;
}

int countingSort(lista *l, long size, long pos)
{
    int *b = (int *)calloc(10, sizeof(int));

    for (long i = 0; i < size; i++)
    {
        int chave = l->elements[i] / pos;
        chave = chave % 10;
        b[chave] = b[chave] + 1;
    }

    for (long i = 1; i < 10; i++)
    {
        b[i] = b[i] + b[i - 1];
    }

    elem *c = malloc(sizeof(lista) * size);
    for (long i = size - 1; i >= 0; i--)
    {
        int chave = l->elements[i] / pos;
        chave = chave % 10;
        b[chave] = b[chave] - 1;
        c[b[chave]] = l->elements[i];
    }

    for (long i = 0; i < size; i++)
    {
        l->elements[i] = c[i];
    }

    free(b);
    free(c);

    return 1;
}

elem maiorNum(lista *l, long size)
{
    elem maior = l->elements[0];

    for (long i = 1; i < size; i++)
    {
        if (maior < l->elements[i])
        {
            maior = l->elements[i];
        }
    }

    return maior;
}

/*-----------------------------------------------------------------------------------------------*/

void realizaMetodoOrdenacao(lista *l, int metodo)
{
    switch (metodo)
    {
    case 1:
        /* Bubble Sort */
        bubbleSort(l);
        break;

    case 2:
        /* Bubble Sort Otimizado*/
        bubbleSortAprimorado(l);
        break;

    case 3:
        /* Quicksort */
        quickSort(l, 0, l->tamanho - 1);
        break;

    case 4:
        /* Radixsort */
        radixSort(l);
        break;

    case 5:
        /* Heap Sort */
        heapSort(l, l->tamanho);
        break;

    default:
        break;
    }
}