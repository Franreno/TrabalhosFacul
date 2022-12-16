#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoesFornecidas.h"
#include "pessoa.h"

void func1()
{
    char *fileName;
    char tempFile[] = "temp.bin";

    // %ms Dinamically allocate memory of the size of string fileName.
    scanf(" %ms", &fileName);

    FILE *readFile = fopen(fileName, "rb");

    if (readFile == NULL)
    {
        printf("Arquivo não encontrado\n");
        return;
    }

    FILE *writeFile = fopen(tempFile, "wb");
    PESSOA *p = pessoaRead(readFile);

    while (p != NULL)
    {
        if (p->removed == '1')
        {
            pessoaWrite(writeFile, p);
        }

        p = pessoaRead(readFile);
    }

    fclose(readFile);
    fclose(writeFile);

    remove(fileName);
    rename(tempFile, fileName);

    binarioNaTela(fileName);
}

void func2()
{
    char *fileName, *fieldName, *fieldValue;
    scanf(" %ms", &fileName);

    FILE *readFile = fopen(fileName, "rb");
    if (readFile == NULL)
    {
        printf("Arquivo não encontrado\n");
        return;
    }

    scanf(" %ms %ms", &fieldName, &fieldValue);


    PESSOA *p = pessoaRead(readFile);

    int hasBeenFounded = 0;

    while (p != NULL)
    {
        if (p->removed == '1')
        {
            if (!strcmp(fieldValue, p->firstName))
            {
                hasBeenFounded = 1;
                pessoaPrint(p);
            }
            else if (!strcmp(fieldValue, p->lastName))
            {
                hasBeenFounded = 1;
                pessoaPrint(p);
            }
            else if (!strcmp(fieldValue, p->email))
            {
                hasBeenFounded = 1;
                pessoaPrint(p);
            }
            else if (!strcmp(fieldValue, p->nationality))
            {
                hasBeenFounded = 1;
                pessoaPrint(p);
            }
        }

        p = pessoaRead(readFile);
    }

    if (!hasBeenFounded)
        printf("Registro não encontrado\n");
}

int main()
{
    int cmd;
    scanf("%d", &cmd);

    switch (cmd)
    {
    case 1:
        func1();
        break;
    case 2:
        func2();
        break;

    default:
        break;
    }
}