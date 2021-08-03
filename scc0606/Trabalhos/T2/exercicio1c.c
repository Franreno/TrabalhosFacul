/*
    Autores:
        Francisco Reis Nogueira - 11954374
        Joao Augusto Fernandes Barbosa - 11953348
        Vinicius Santos Cubi Paulo - 11965693
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definição das variaveis que controlam a medição de tempo
clock_t _ini, _fim;

// Definição do tipo booleano
unsigned char typedef bool;
#define TRUE  1
#define FALSE 0

int* ler_inteiros(const char * arquivo, const int n)
{
    FILE* f = fopen(arquivo, "r");

    int * inteiros = (int *) malloc(sizeof(int) * n);

    for (int i = 0; !feof(f); i++)
        fscanf(f, "%d\n", &inteiros[i]);

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


int busca_seq_t(int **tabela, int n, int e);
int main(int argc, char const *argv[])
{
    const int N = 50000;
    unsigned encontrados = 0;

    int* entradas = ler_inteiros("inteiros_entrada.txt", N);
    int* consultas = ler_inteiros("inteiros_busca.txt", N);




    // realiza busca sequencia com realocação
    inicia_tempo();
    for (int i = 0; i < N; i++) {
        // buscar o elemento consultas[i] na entrada

        encontrados = encontrados + busca_seq_t(&entradas,N,consultas[i]);

    }
    double tempo_busca = finaliza_tempo();

    printf("Tempo de busca    :\t%fs\n", tempo_busca);
    printf("Itens encontrados :\t%d\n", encontrados);
    return 0;




}
//função de busca sequencial com o método da transposição
int busca_seq_t(int **tabela, int n, int e){
  if((*tabela)[0] == e){ //caso seja encontrado no primeiro endereço nada precisa ser feito
    return 1;
  }

  for (int i = 1; i < n; i++){// caso não esteja no primeiro endereço do vetor a chave deve ser movida uma casa a frente
      if ((*tabela)[i] == e){
          int tmp  = (*tabela)[i-1];
          (*tabela)[i-1] = (*tabela)[i];
          (*tabela)[i] = tmp;
          return 1;
      }
    }
    return 0;
}
