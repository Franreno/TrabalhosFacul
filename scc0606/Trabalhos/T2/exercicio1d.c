/*
    Autores:
        Francisco Reis Nogueira - 11954374
        Joao Augusto Fernandes Barbosa - 11953348
        Vinicius Santos Cubi Paulo - 11965693
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 50000

struct info{
    int valor;
};

struct lista{
    int qtd;
    struct info dados[MAX];
};

typedef struct lista Lista;

Lista* cria_lista(){
    Lista *li;
    li = (Lista*) malloc(sizeof(struct lista));
    if(li != NULL)
        li->qtd = 0;
    return li;
}

void libera_lista(Lista* li){
    free(li);
}

int insere_lista_ordenada(Lista* li, int n){
    if(li == NULL)
        return 0;
    if(li->qtd == MAX)//lista cheia
        return 0;
    int k,i = 0;
    while(i<li->qtd && li->dados[i].valor < n)
        i++;

    for(k=li->qtd-1; k >= i; k--)
        li->dados[k+1] = li->dados[k];

    li->dados[i].valor = n;
    li->qtd++;
    return 1;
}


//Definição para a busca indexada
typedef int elem;

typedef struct {
    elem kindex;
    int pos;
} elem_i;


int busca_sequencial_indexada(Lista* li, int n, int e, elem_i tabela_i[], int t) {
     int pos_index;
     int i;
     for(i = 0; i < t; i++){
        if(tabela_i[i].kindex > e){
            break;
        }
     }

    i--;
    if(i == -1){
        return -1;
    }

    for(int k = tabela_i[i].pos; k < n ; k++){
        
        
        if(li->dados[k].valor == e){
           
            return 1;
        }
    }

         
        return -1;
     }


// Definição das variaveis que controlam a medição de tempo
clock_t _ini, _fim;

// Definição do tipo booleano
unsigned char typedef bool;
#define TRUE  1
#define FALSE 0

int* ler_inteiros(const char * arquivo, const int n, Lista* li, int opt)
{
    FILE* f = fopen(arquivo, "r");

    int* inteiros = (int *) malloc(sizeof(int) * n);

    for (int i = 0; !feof(f); i++){
        fscanf(f, "%d\n", &inteiros[i]);
        if(opt == 1)
            insere_lista_ordenada(li, inteiros[i]);
    }
    fclose(f);

    return inteiros;
}

void inicia_tempo()
{
    srand(time(NULL));
    _ini = clock();
}

double finaliza_tempo()
{
    _fim = clock();
    return ((double) (_fim - _ini)) / CLOCKS_PER_SEC;
}

int main(int argc, char const *argv[])
{
    const int N = 50000;
    const int index_size = 10000;
    unsigned encontrados = 0;
    Lista* li = cria_lista();


    int* entradas = ler_inteiros("inteiros_entrada.txt", N, li, 1);
    int* consultas = ler_inteiros("inteiros_busca.txt", N, li, 0);
    
    // ordenação ja realizada na inserção

    // criar tabela de indice

    int retorno, n = 50000, t = 5; 
    elem_i tabela_i[t];
    for (int i = 0; i < t; i++) {
        tabela_i[i].pos = i * n / t; // identificar e guardar a posicao
        tabela_i[i].kindex = li->dados[tabela_i[i].pos].valor; // guardar o valor
    }

   
    
    // realizar consultas na tabela de indices 
    inicia_tempo();
    for (int i = 0; i < N; i++) {
       retorno = busca_sequencial_indexada(li,  n, consultas[i], tabela_i, t);
       if(retorno == 1){
           encontrados++;
       }
    }
    double tempo_busca = finaliza_tempo();

    printf("Tempo de busca    :\t%fs\n", tempo_busca);
    printf("Itens encontrados :\t%d\n", encontrados);

    return 0;
}
