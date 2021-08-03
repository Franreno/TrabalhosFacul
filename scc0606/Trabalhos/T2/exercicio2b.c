/*
    Autores:
        Francisco Reis Nogueira - 11954374
        Joao Augusto Fernandes Barbosa - 11953348
        Vinicius Santos Cubi Paulo - 11965693
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> // funções strcmp e strcpy
#include <math.h>

//declarando a estrutura de hash
typedef char *string;
typedef string elem;
typedef struct {
  elem *vet;
}hash;

// Definição das variaveis que controlam a medição de tempo
clock_t _ini, _fim;

// Definição do tipo booleano
typedef unsigned char bool;
#define TRUE  1
#define FALSE 0

// Definição do tipo string
typedef char * string;

#define MAX_STRING_LEN 20


unsigned converter(string s) {
   unsigned h = 0;
   for (int i = 0; s[i] != '\0'; i++)
      h = h * 256 + s[i];
   return h;
}

string* ler_strings(const char * arquivo, const int n)
{
    FILE* f = fopen(arquivo, "r");

    string* strings = (string *) malloc(sizeof(string) * n);

    for (int i = 0; !feof(f); i++) {
        strings[i] = (string) malloc(sizeof(char) * MAX_STRING_LEN);
        fscanf(f, "%s\n", strings[i]);
    }

    fclose(f);

    return strings;
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

unsigned h_div(unsigned x, unsigned i, unsigned B)
{
    return ((x % B) + i) % B;
}

unsigned h_mul(unsigned x, unsigned i, unsigned B)
{
    const double A = 0.6180;
    return  ((int) ((fmod(x * A, 1) * B) + i)) % B;
}

int hash_duplo(unsigned x, unsigned i, unsigned  B)
{
    return  ((int) (h_mul(x,i,B)+i*h_div(x,i,B))% B);//retorna funcao hashing dupla
}


#define N  50000
#define M  70000
#define B  150001

//inicializando o vetor hash com todos os valores vazios (utilizado -1 como identificação de vazio)
void inicializar(hash *tabela) {
  tabela->vet = (elem*)malloc(sizeof(elem)*B);
  for (int i = 0; i < B; i++)
      tabela->vet[i] = " ";
}

//Limpar todos os dados do vetor hash
void limpar(hash *tabela) {
  free(tabela->vet);
}

//função de inserir dados no vetor hash se utilizando da técnica rehash, overflow progressivo
int inserir_div(hash *tabela, elem e) {
  int pos;
  int i = 0;
  for (; i < B; i++) // caso a posição já esteja ocupada é realizado o rehash até encontrar uma posição livre
  {
    pos = hash_duplo(converter(e),i,B); // calcula endereco
    if (strcmp(tabela->vet[pos]," ") == 0) {
        tabela->vet[pos] = e;
        break;
      }
    if(strcmp(tabela->vet[pos], e) == 0)
      return 0;
    }

    if(i == 0){

      return 0;

    }else{

      return 1;
    }
}

//função de busca de infomrações no vetor hash
int buscar_div(hash *tabela, elem e){
  int pos;
  for (int i = 0; i < B; i++) { //caso não seja encontrado na posição determinada pela função h(k,0) é tentado novamente a busca pela tecnica de rehash
    pos = hash_duplo(converter(e),i,B);
  if (strcmp(tabela->vet[pos],e) == 0)
    return 1;
  if (strcmp(tabela->vet[pos]," ") == 0)
    return 0;
  }
  return 0;

}






int main(int argc, char const *argv[])
{


    unsigned colisoes = 0;
    

    unsigned encontrados = 0;
   

    string* insercoes = ler_strings("strings_entrada.txt", N);
    string* consultas = ler_strings("strings_busca.txt", M);


    hash tabela;
    // cria tabela hash com hash por divisão
    inicializar(&tabela);

    //inserção dos dados na tabela hash usando hash por divisão
    inicia_tempo();
    for (int i = 0; i < N; i++) {

      colisoes= colisoes + inserir_div(&tabela,insercoes[i]);

    }
    double tempo_insercao = finaliza_tempo();

      //consulta dos dados na tabela hash usando hash por divisão
    inicia_tempo();
    for (int i = 0; i < M; i++) {
        // buscar consultas[i] na tabela hash
        encontrados = encontrados + buscar_div(&tabela,consultas[i]);

    }
    double tempo_busca = finaliza_tempo();

    


    printf("Hash por Divisão\n");
    printf("Colisões na inserção: %d\n", colisoes);
    printf("Tempo de inserção   : %fs\n", tempo_insercao);
    printf("Tempo de busca      : %fs\n", tempo_busca);
    printf("Itens encontrados   : %d\n", encontrados);
   
    return 0;


}

