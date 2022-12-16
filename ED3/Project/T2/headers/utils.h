#ifndef __utils__
#define __utils__

/**
 * Autores: 
 * (11800970) Felipe de Alcantra Tome 
 * (11954374) Francisco Reis Nogueira 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

typedef struct _cabecalho
{
    char status;
    long topoLista;
    int nroEstacoes;
    int nroParesEstacao;
} CABECALHO;

typedef struct _registro
{
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
} REGISTRO;

#include "funcoesFornecidas.h"
#include "binary.h"

void printRegistro(REGISTRO *r);
void finalizeRegister(REGISTRO *r);

int outputBinary(FILE *bin);
void copyRegisterContents(REGISTRO *dest, REGISTRO *src);

long getFileSize(FILE *arq);

int parseLine(REGISTRO *r, char *line);
int StringToInt(char *str);
int StringToInt(char *str);
int isNull(char *str);

int parseSingleStringFromBinaryFile(FILE *bin, char **line);

#endif
