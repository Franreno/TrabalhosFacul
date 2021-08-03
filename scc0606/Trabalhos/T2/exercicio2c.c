/*
    Autores:
        Francisco Reis Nogueira - 11954374
        Joao Augusto Fernandes Barbosa - 11953348
        Vinicius Santos Cubi Paulo - 11965693
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <math.h>

// Definição das variaveis que controlam a medição de tempo
clock_t _ini, _fim;

// Definição do tipo booleano
typedef unsigned char bool;
#define TRUE 1
#define FALSE 0

// Definição do tipo string
typedef char *string;

#define MAX_STRING_LEN 20

//------------------------------------Definicoes das structs Listas e Tabela Hash------------------------------------
typedef struct node
{
    char data[MAX_STRING_LEN];
    struct node *next;
} node;

typedef struct node *List;
typedef struct node no;

typedef struct hash
{
    unsigned TAM;
    List *valores;
} hash;

typedef struct hash Hash;

//-------------------------------------------------------------------------------------------------------------------

unsigned converter(string s)
{
    unsigned h = 0;
    for (int i = 0; s[i] != '\0'; i++)
        h = h * 256 + s[i];
    return h;
}

string *ler_strings(const char *arquivo, const int n)
{
    FILE *f = fopen(arquivo, "r");

    string *strings = (string *)malloc(sizeof(string) * n);

    for (int i = 0; !feof(f); i++)
    {
        strings[i] = (string)malloc(sizeof(char) * MAX_STRING_LEN);
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
    return ((double)(_fim - _ini)) / CLOCKS_PER_SEC;
}

unsigned h_div(unsigned x, unsigned B)
{
    return x % B;
}

unsigned h_mul(unsigned x, unsigned B)
{
    const double A = 0.6180;
    return fmod(x * A, 1) * B;
}

//------------------------------------Inicio Definicao das funcoes da Lista encadeada------------------------------------

//Cria $TAM listas
List *createList(unsigned TAM)
{
    List *li = (List *)malloc(TAM * sizeof(List));
    if (li != NULL)
    {
        for (int i = 0; i < TAM; i++)
        {
            li[i] = NULL;
        }
        return li;
    }
}

//Libera as listas
void deleteList(List *li, int TAM)
{
    if (li != NULL)
    {
        for (int i = 0; i < TAM; i++)
            free(li[i]);

        free(li);
    }
}

//Insere uma das strings em uma das listas da tabela hash
int insereLista(List *li, string data)
{
    int houveColisao = FALSE;
    no *newNode = (no *)malloc(sizeof(no));
    strcpy(newNode->data, data);

    if ((*li) != NULL) //Se a lista nao apontar pra NULL eh pq teve colisao.
        houveColisao = TRUE;

    newNode->next = (*li);
    (*li) = newNode;

    return houveColisao;
}

//Procura uma string em uma das listas da tabela hash
int buscaLista(node *ptr, string data)
{
    while (ptr != NULL)
    {
        if (strcmp(ptr->data, data) == 0)
            return TRUE;

        ptr = ptr->next;
    }

    return FALSE;
}
//------------------------------------Fim Definicao das funcoes da Lista encadeada---------------------------------------

//------------------------------------Inicio Definicao das funcoes da tabela Hash------------------------------------

//Cria a tabela Hash
Hash *createHash(unsigned TAM)
{
    Hash *h = (Hash *)malloc(sizeof(Hash));
    if (h != NULL)
    {
        h->TAM = TAM;
        h->valores = createList(TAM);
        if (h->valores != NULL)
            return h;
    }
}

// Libera a tabela Hash
void deleteHash(Hash *h)
{
    if (h == NULL)
        return;
    for (int i = 0; i < h->TAM; i++)
    {
        if (h->valores[i] != NULL)
            free(h->valores[i]);
    }
    free(h->valores);
    free(h);
}


//Busca uma string na tabela hash utilizando uma funcao hash a ser especificada
int buscaHash(unsigned (*func)(unsigned, unsigned), Hash *h, string data)
{
    if (h == NULL)
        return -1;

    int pos = func(converter(data), h->TAM);

    //Busca na lista da posicao da tabela
    if (!buscaLista(h->valores[pos], data))
    {
        return FALSE;
    }

    return TRUE;
}

// Insere uma string na tabela hash utilizando uma funcao hash a ser especificada
int insereHash(unsigned (*func)(unsigned, unsigned), Hash *h, string data)
{
    if (h == NULL)
        return -1;

    int pos = func(converter(data), h->TAM);

    // Verificar se o dado ja existe no Hash para nao inserir duas vezes
    if (buscaLista(h->valores[pos], data))
        return FALSE;

    // Inserir na Lista, se retornar 0 nao houve colisao.    
    if(!insereLista(&h->valores[pos], data) )
        return FALSE;

    return TRUE;
}
//------------------------------------Fim Definicao das funcoes da tabela Hash---------------------------------------

int main(int argc, char const *argv[])
{
    const int N = 50000;
    const int M = 70000;
    const int B = 150001;

    unsigned colisoes_h_div = 0;
    unsigned colisoes_h_mul = 0;

    unsigned encontrados_h_div = 0;
    unsigned encontrados_h_mul = 0;

    string *insercoes = ler_strings("strings_entrada.txt", N);
    string *consultas = ler_strings("strings_busca.txt", M);

    // cria tabela hash com hash por divisão
    Hash *h_di = createHash(B);

    // inserção dos dados na tabela hash com hash por divisão
    inicia_tempo();
    for (int i = 0; i < N; i++)
    {
        // inserir insercoes[i] na tabela hash
        if (insereHash(&h_div, h_di, insercoes[i]))
            colisoes_h_div++;
    }
    double tempo_insercao_h_div = finaliza_tempo();

    // busca dos dados na tabela hash com hash por divisão
    inicia_tempo();
    for (int i = 0; i < M; i++)
    {
        // buscar consultas[i] na tabela hash
        if (buscaHash(&h_div, h_di, consultas[i]))
            encontrados_h_div++;
    }
    double tempo_busca_h_div = finaliza_tempo();

    // destroi tabela hash com hash por divisão
    deleteHash(h_di);

    // cria tabela hash com hash por multiplicação
    Hash *h_mu = createHash(B);

    // inserção dos dados na tabela hash com hash por multiplicação
    inicia_tempo();
    for (int i = 0; i < N; i++)
    {
        // inserir insercoes[i] na tabela hash
        if (insereHash(&h_mul, h_mu, insercoes[i]))
            colisoes_h_mul++;
    }
    double tempo_insercao_h_mul = finaliza_tempo();

    // busca dos dados na tabela hash com hash por multiplicação
    inicia_tempo();
    for (int i = 0; i < M; i++)
    {
        // buscar consultas[i] na tabela hash
        if (buscaHash(&h_mul, h_mu, consultas[i]))
            encontrados_h_mul++;
    }
    double tempo_busca_h_mul = finaliza_tempo();

    // destroi tabela hash com hash por multiplicação
    deleteHash(h_mu);

    printf("Hash por Divisão\n");
    printf("Colisões na inserção: %d\n", colisoes_h_div);
    printf("Tempo de inserção   : %fs\n", tempo_insercao_h_div);
    printf("Tempo de busca      : %fs\n", tempo_busca_h_div);
    printf("Itens encontrados   : %d\n", encontrados_h_div);
    printf("\n");
    printf("Hash por Multiplicação\n");
    printf("Colisões na inserção: %d\n", colisoes_h_mul);
    printf("Tempo de inserção   : %fs\n", tempo_insercao_h_mul);
    printf("Tempo de busca      : %fs\n", tempo_busca_h_mul);
    printf("Itens encontrados   : %d\n", encontrados_h_mul);

    return 0;
}
