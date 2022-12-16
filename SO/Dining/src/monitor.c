/**
 * Francisco Reis Nogueira
 * 11954374
 */

#include "dining.h"

enum
{
    pensando,
    comFome,
    comendo
} state[5];

// Semaforos
sem_t mutex, next_sem;

// Counter da quantidade de processos suspensos
int next_counter = 0;

typedef struct
{
    sem_t semaphor;

    int quantidadeEsperando; // quantidade de filosofos esperando esse semaforo

} condicoes;

condicoes garfos[5];

void pegarGarfo(int i)
{
    sem_wait(&mutex);
    state[i] = comFome;

    // Verificar se pode comer olhando os garfos ao seu lado
    olharGarfos(i);

    if (state[i] != comendo)
    {
        emEspera(i);
    }

    if (next_counter > 0)
    {
        sem_post(&next_sem);
    }
    else
    {
        sem_post(&mutex);
    }
}

void deixarGarfo(int i)
{
    sem_wait(&mutex);
    state[i] = pensando;

    olharGarfos((i + 1) % 5);
    olharGarfos((i + 4) % 5);

    if (next_counter > 0)
    {
        sem_post(&next_sem);
    }
    else
    {
        sem_post(&mutex);
    }
}

void olharGarfos(int i)
{
    // Verificar se os filosofos ao redor de i estao comendo
    if ((state[(i + 1) % 5] != comendo) && state[(i + 4) % 5] != comendo && state[i] == comFome)
    {
        // se nao estiverem setar este filosofo para comer
        state[i] = comendo;
    }
    sinalizar(i);
}

void sinalizar(int i)
{
    if (garfos[i].quantidadeEsperando > 0)
    {
        next_counter++;
        sem_post(&garfos[i].semaphor);
        sem_wait(&next_sem);
        next_counter--;
    }
}

void emEspera(int i)
{
    garfos[i].quantidadeEsperando++;

    if (next_counter > 0)
    {
        sem_post(&next_sem);
    }
    else
    {
        sem_post(&mutex);
    }

    sem_wait(&garfos[i].semaphor);
    garfos[i].quantidadeEsperando--;
}

void inicializar()
{
    // Inicializar os semaforos principais e os garfos

    sem_init(&mutex, 0, 1);
    sem_init(&next_sem, 0, 0);

    for (int i = 0; i < 5; i++)
    {
        state[i] = pensando;
        sem_init(&garfos[i].semaphor, 0, 0);
        garfos[i].quantidadeEsperando = 0;
    }
}