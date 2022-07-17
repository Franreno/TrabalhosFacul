#ifndef __binary__
#define __binary__

/**
 * Autores: 
 * (11800970) Felipe de Alcantra Tome 
 * (11954374) Francisco Reis Nogueira 
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "registro.h"
#include "list.h"
#include "parser.h"
#include "utils.h"

// Write Functions
int writeBin(FILE *bin, REGISTRO *r);
void writeCabecalho(FILE *bin, CABECALHO *c);
void writeStringAtBinary(FILE *bin, REGISTRO *r);
int writeStringNomeEstacao(FILE *bin, REGISTRO *r);
int writeStringNomeLinha(FILE *bin, REGISTRO *r);
void writeIntegerAtBinary(FILE *bin, REGISTRO *r);
void writeTrash(FILE *bin, int n);
void rewriteCabecalho(CABECALHO *c, FILE *bin);

// Read Functions
void readCabecalho(CABECALHO *c, FILE *bin);
void readFirstThreeFields(REGISTRO *r, FILE *bin);
void readIntegerFieldsAtRegister(REGISTRO *r, FILE *bin);
void readStringFieldsAtRegister(REGISTRO *r, FILE *bin);
int readSingleRegister(REGISTRO *r, FILE *bin);
int readFromRemovedRegister(REGISTRO *reg, FILE *bin, int *optimalSize);


void searchUpdatePositions(FILE *bin, CABECALHO *c, REGISTRO *busca, int amountOfBuscaFields, REGISTRO *att, int amountOfAttFields);

#endif