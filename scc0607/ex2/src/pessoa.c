#include <stdlib.h>

#include "pessoa.h"

PESSOA *pessoaCreate()
{
    PESSOA *p = (PESSOA *)malloc(sizeof(PESSOA));
    if (p == NULL)
        return NULL;

    p->removed = '1';

    for (int i = 0; i < firstNameSize; i++)
    {
        p->firstName[i] = trashChar;
        p->lastName[i] = trashChar;
        p->email[i] = trashChar;
        p->nationality[i] = trashChar;
    }
    for (int i = firstNameSize; i < emailSize; i++)
        p->email[i] = trashChar;

    p->age = -1;

    return p;
}

PESSOA *pessoaRead(FILE *file)
{
    PESSOA *p = pessoaCreate();

    size_t lidos = fread(&p->removed, sizeof(char), 1, file);

    if (lidos < 1)
        return NULL;

    fread(p->firstName, sizeof(char), firstNameSize, file);
    fread(p->lastName, sizeof(char), lastNameSize, file);
    fread(p->email, sizeof(char), emailSize, file);
    fread(p->nationality, sizeof(char), nationalitySize, file);
    fread(&p->age, sizeof(int), 1, file);

    return p;
}

void pessoaWrite(FILE *file, PESSOA *p)
{
    if (file == NULL || p == NULL)
        return;

    fwrite(&p->removed, sizeof(char), 1, file);
    fwrite(p->firstName, sizeof(char), firstNameSize, file);
    fwrite(p->lastName, sizeof(char), lastNameSize, file);
    fwrite(p->email, sizeof(char), emailSize, file);
    fwrite(p->nationality, sizeof(char), nationalitySize, file);
    fwrite(&p->age, sizeof(int), 1, file);
}


void pessoaPrint(PESSOA *p)
{
    printf("Firstname: %s\nLastname: %s\nEmail: %s\nNationality: %s\nAge: %d\n\n", p->firstName, p->lastName, p->email, p->nationality, p->age);
}
