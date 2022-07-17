#ifndef __PARSER__
#define __PARSER__

/**
 * Autores: 
 * (11800970) Felipe de Alcantra Tome 
 * (11954374) Francisco Reis Nogueira 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "registro.h"

int parseLine(REGISTRO *r, char *line);
int StringToInt(char *str);
int StringToInt(char *str);
int isNull(char *str);

int parseSingleStringFromBinaryFile(FILE *bin, char **line);

#endif