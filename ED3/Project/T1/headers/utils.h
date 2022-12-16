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

#include "registro.h"
#include "list.h"

void scanIntegerInputs(int *value, char **str);
void scanStringInputs(char **strValue, char **auxStr);
long getFileSize(FILE *arq);

void cleanUpdateRegister(REGISTRO *r);
void validateUpdateStrings(REGISTRO *r);
int scanCampoInput();
int applyValueAtRegister(REGISTRO *r, int position);
void createUpdateRegisterInputs(REGISTRO *r, int *amountOfFields);

int validateBuscaWithRegisterRead(REGISTRO *aux, REGISTRO *busca, int amountOfBuscaFields);

void updateIntegersAtNewRegisterInsert(int *dest, int *originalSource, int *updatedSource);
void updateStringsAtRemovedInsert(char **dest, char **originalSource, char **updatedSource);

#endif