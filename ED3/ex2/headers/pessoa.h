#ifndef __PESSOA__
#define __PESSOA__

#include <stdio.h>

#define fileNameSize 51
#define firstNameSize 51
#define lastNameSize 51
#define emailSize 81
#define nationalitySize 51

#define trashChar '$'

typedef struct _pessoa
{
    char removed;
    char firstName[firstNameSize];
    char lastName[lastNameSize];
    char email[emailSize];
    char nationality[nationalitySize];
    int age;

} PESSOA;

PESSOA *pessoaCreate();
PESSOA *pessoaRead(FILE *file);
void pessoaWrite(FILE *file, PESSOA *p);
void pessoaPrint(PESSOA *p);

#endif