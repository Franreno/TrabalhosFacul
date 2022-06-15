#ifndef __DINING__
#define __DINING__

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

void inicializar();
void olharGarfos(int i);
void pegarGarfo(int i);
void deixarGarfo(int i);
void emEspera(int i);
void sinalizar(int i);

#endif