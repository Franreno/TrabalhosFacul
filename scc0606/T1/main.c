/*
    Francisco Reis Nogueira - 11954374
    Joao Augusto Fernandes Barbosa - 11953348
    Vinicius Cubi Santos Paulo -11965693
*/

#include "sorting.h"

int main()
{
    printf("Bubble sort, Aleatorio\n");
    calculaEmpirico(1, Aleatorio);
    printf("---------------------------------\n");

    printf("Bubble sort, Ordenado\n");
    calculaEmpirico(1, Ordenado);
    printf("---------------------------------\n");

    printf("Bubble sort, Invertido\n");
    calculaEmpirico(1, Invertido);
    printf("---------------------------------\n");

    /*------------------------------------------------------------*/

    printf("Bubble sort Aprimorado, Aleatorio\n");
    calculaEmpirico(2, Aleatorio);
    printf("---------------------------------\n");

    printf("Bubble sort Aprimorado, Ordenado\n");
    calculaEmpirico(2, Ordenado);
    printf("---------------------------------\n");

    printf("Bubble sort Aprimorado, Invertido\n");
    calculaEmpirico(2, Invertido);
    printf("---------------------------------\n");

    /*------------------------------------------------------------*/

    printf("Quicksort, Aleatorio\n");
    calculaEmpirico(3, Aleatorio);
    printf("---------------------------------\n");

    printf("Quicksort, Ordenado\n");
    calculaEmpirico(3, Ordenado);
    printf("---------------------------------\n");

    printf("Quicksort, Invertido\n");
    calculaEmpirico(3, Invertido);
    printf("---------------------------------\n");

    /*------------------------------------------------------------*/

    printf("Radix sort, Aleatorio\n");
    calculaEmpirico(4, Aleatorio);
    printf("---------------------------------\n");

    printf("Radix sort, Ordenado\n");
    calculaEmpirico(4, Ordenado);
    printf("---------------------------------\n");

    printf("Radix sort, Invertido\n");
    calculaEmpirico(4, Invertido);
    printf("---------------------------------\n");

    /*------------------------------------------------------------*/
    printf("Heapsort, Aleatorio\n");
    calculaEmpirico(5, Aleatorio);
    printf("---------------------------------\n");

    printf("Heapsort, Ordenado\n");
    calculaEmpirico(5, Ordenado);
    printf("---------------------------------\n");

    printf("Heapsort, Invertido\n");
    calculaEmpirico(5, Invertido);
    printf("---------------------------------\n");

    /*------------------------------------------------------------*/

    return 0;
}
/*
    Funcao escolheTipo:
        Define o tamanho maximo para cada tipo de ordenacao
*/
void escolheTipo(int metodo, long *tamanho)
{
    switch (metodo)
    {
    case 1:
        /* Bubble Sort */
        (*tamanho) = TAM_BUBBLE;
        break;

    case 2:
        /* Bubble Sort Otimizado*/
        (*tamanho) = TAM_BUBBLEOT;
        break;

    case 3:
        /* Quicksort */
        (*tamanho) = TAM_QUICK;
        break;

    case 4:
        /* Radixsort */
        (*tamanho) = TAM_RADIX;
        break;

    case 5:
        /* Heap Sort */
        (*tamanho) = TAM_HEAP;
        break;

    default:
        tamanho = NULL;
        break;
    }
}

/*
    Funcao calculaEmpirico:
        Uma funcao que realiza a analise empirica como nas aulas,
        precisa receber o tipo de ordenacao [1,5] e o metodo de criacao do vetor [1,3].
        
        A cada repeticao da medicao do tempo a funcao armazena o valor em um vetor para que
        seja possivel o calculo da media do tempo e do desvio padrao do tempo.

        O tamanho de cada lista cresce em um fator de 10, ou seja, 100 -> 1000 -> 10000, etc.

    metodo 1: Bubble sort
    metodo 2: Bubble sort Otimizado
    metodo 3: Quicksort
    metodo 4: Radixsort
    metodo 5: Heap sort

    metodoCriacao 1: Aleatorio
    metodoCriacao 2: Ordenado
    metodoCriacao 3: Invertido
*/

void calculaEmpirico(int metodo, int metodoCriacao)
{
    long TAM_MAX;
    escolheTipo(metodo, &TAM_MAX);

    lista l;
    clock_t tempoIni;
    double arrTempo[Repeticoes];

    for (int i = 2; pow(10, i) <= TAM_MAX; i++) //Crescimento em um fator de 10
    {
        for (int j = 0; j < Repeticoes; j++) //Realiza 10 repeticoes e utiliza-se a media deste valor
        {

            // Cria a lista com tamanho igual a pow(10,i)
            criaLista(&l, pow(10, i));

            // Inserir elementos na lista
            insereMetodoCriacao(&l, pow(10, i), metodoCriacao);

            // Realiza o metodo
            tempoIni = clock();
            realizaMetodoOrdenacao(&l, metodo);
            arrTempo[j] = ( (double)clock() - tempoIni ) / CLOCKS_PER_SEC;
            
            apagaLista(&l);
        }
        double media = calculaMedia(arrTempo);
        double desvioPadrao = calculaDesvioPadrao(arrTempo, media);

        //Tempo medio percorrido
        printf("Quantidade: %ld    Tempo: %0.10lf    Desvio Padrao: %0.10lf\n", (long)pow(10, i), (media), desvioPadrao);
    }
}


/*
    Calcula a media dos valores de medicao
*/
double calculaMedia(double *vec)
{
    double somaTempo = 0;
    for (int i = 0; i < Repeticoes; i++)
        somaTempo += vec[i];
    return somaTempo/ Repeticoes;
}

/*
    Calcula o desvio padrao dos valores de tempo medidos.
*/
double calculaDesvioPadrao(double *vec, double media)
{
    double somaTempo = 0;
    for (int i = 0; i < Repeticoes; i++)
        somaTempo += pow((vec[i] - media), 2);

    return sqrt(somaTempo / Repeticoes);
}