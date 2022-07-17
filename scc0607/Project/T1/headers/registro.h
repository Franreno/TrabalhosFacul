#ifndef __REGISTRO__
#define __REGISTRO__

/**
 * Autores: 
 * (11800970) Felipe de Alcantra Tome 
 * (11954374) Francisco Reis Nogueira 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

// Caractere lixo
#define trashChar "$"

// Status
#define CONSISTENTE '1'
#define INCONSISTENTE '0'

// Removido
#define REMOVIDO '1'
#define NAOREMOVIDO '0'

// Delimitador de strings
#define DELIMITADOR '|'

// Null para tamanho fixo
#define NULLFIXO -1

typedef struct _cabecalho {
    char status;
    long topoLista;
    int nroEstacoes;
    int nroParesEstacao;
}CABECALHO;

typedef struct _registro {
    char removido;
    int tamanhoRegistro;
    long proxLista;
    int codEstacao;
    int codLinha;
    int codProxEstacao;
    int distProxEstacao;
    int codLinhaIntegra;
    int codEstIntegra;
    char *nomeEstacao; // Termina com |
    char *nomeLinha;   // Termina com |
}REGISTRO;


#include "funcoesFornecidas.h"
#include "parser.h"
#include "binary.h"


void printRegistro(REGISTRO *r);
void finalizeRegister(REGISTRO *r);
int scanInsertInputs(REGISTRO *r);
int scanUpdateInputs(REGISTRO *busca, int *amountOfBuscaFields, REGISTRO *att, int *amountOfAttFields);


int readAndWriteCSV(FILE *csv, FILE *bin);
int outputBinary(FILE *bin);

int buscaRegistro(FILE *bin, long fileSize, REGISTRO *r, char **stringValorCampo, int *campoValor, int n, int *campos, List *total, int *nroPares, int *nroEstacoes, long *ultimoRemovido);
int coletaDeDados(int *campoValor, char **stringValorCampo, int *campos);

int searchForOptimalPosition(long *topoLista, REGISTRO *r, FILE *bin);
int insertNTimes(FILE *bin);

void createNewRegisterWithUpdatedData(REGISTRO *newRegister, REGISTRO *aux, REGISTRO *att);

void deleteRegistros(FILE *bin, List *alteracoes, long ultimoRemovido);


#endif
