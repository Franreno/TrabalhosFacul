#include <stdio.h>
#include <stdlib.h>
#include "ex1.h"

/*
    Writes n times in a file the data from user's input
*/
void func1(char file[], PESSOA *p)
{
    FILE *fp = NULL;
    fp = fopen(file, "wb");
    int nRegisters;
    scanf("%d", &nRegisters);
    for (int i = 0; i < nRegisters; i++)
    {
        readPessoaStdin(p);

        writePessoa(fp, p);
    }
    fclose(fp);
    binarioNaTela(file);
}

/*
    Reads everything from a file
*/
void func2(char file[])
{
    FILE *fp = fopen(file, "rb");
    if (fp == NULL)
        return;

    readEverything(fp);
    fclose(fp);
}

/*
    Read an especific register from a file
*/
void func3(char file[])
{
    FILE *fp = fopen(file, "rb");
    if (fp == NULL)
        return;
    int registerToBeRead;
    scanf("%d", &registerToBeRead);

    readRegister(fp, registerToBeRead);
}

int main()
{
    int cmd;
    char file[fileNameSize];
    PESSOA p;

    scanf("%d", &cmd);
    scanf("%s", file);

    switch (cmd)
    {
    case 1:
        func1(file, &p);
        break;

    case 2:
        func2(file);
        break;

    case 3:
        func3(file);
        break;

    default:
        break;
    }

    return 0;
}