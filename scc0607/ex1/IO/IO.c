#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ex1.h"

/*
    Reads from stdin the user's input for the struct PESSOA fields.
*/
int readPessoaStdin(PESSOA *p)
{
    if (p == NULL)
        return 0;

    readline(p->firstName);
    readline(p->lastName);
    readline(p->email);
    readline(p->nationality);

    scanf("%d", &p->age);

    return 1;
}

/*
    Fill the empty space with trash signs, aka as "$".
*/
void writeTrash(FILE *fp, int n)
{
    for (int i = 0; i < n; i++)
        fwrite(trashChar, sizeof(char), 1, fp);
}

/*
    Write fields from the struct PESSOA into a binary file.
*/
int writePessoa(FILE *fp, PESSOA *p)
{
    if (fp == NULL || p == NULL)
        return 0;

    //Writes fisrtName.
    //Strlen doesn't count \0, but the assignment needs it to be included, therefore +1.
    int fieldSize = strlen(p->firstName) + 1;
    fwrite(p->firstName, sizeof(char), fieldSize, fp);
    writeTrash(fp, firstNameSize - fieldSize);

    //Writes lastName.
    fieldSize = strlen(p->lastName) + 1;
    fwrite(p->lastName, sizeof(char), fieldSize, fp);
    writeTrash(fp, lastNameSize - fieldSize);

    //Writes email.
    fieldSize = strlen(p->email) + 1;
    fwrite(p->email, sizeof(char), fieldSize, fp);
    writeTrash(fp, emailSize - fieldSize);

    //Writes nationality.
    fieldSize = strlen(p->nationality) + 1;
    fwrite(p->nationality, sizeof(char), fieldSize, fp);
    writeTrash(fp, nationalitySize - fieldSize);

    //Writes age.
    fwrite(&p->age, sizeof(int), 1, fp);

    return 1;
}

/*
    Print the fields from a PESSOA's struct.
*/
void printFields(PESSOA *p)
{
    printf("Firstname: %s\nLastname: %s\nEmail: %s\nNationality: %s\nAge: %d\n\n", p->firstName, p->lastName, p->email, p->nationality, p->age);
}

/*
    Reads everything from a file.
    Uses fseek to get the ammount of bytes from the file and 
    loops through it while reading it's content.
*/
int readEverything(FILE *fp)
{
    PESSOA p;

    //Get number of bytes (size) from file.
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    //Loops through it until hits the file's 'size' limit.
    while (ftell(fp) != size)
    {
        fread(p.firstName, sizeof(char), firstNameSize, fp);
        fread(p.lastName, sizeof(char), lastNameSize, fp);
        fread(p.email, sizeof(char), emailSize, fp);
        fread(p.nationality, sizeof(char), nationalitySize, fp);
        fread(&p.age, sizeof(int), 1, fp);
        printFields(&p);
    }

    return 1;
}

/*
    Reads a single register from a binary file.
    Uses an offset with the knowledge of each PESSOA's field size to 
    jump to an especific location on the file.
*/
int readRegister(FILE *fp, int registerToBeRead)
{
    PESSOA p;

    int offsetBaseValue = (firstNameSize + lastNameSize + emailSize + nationalitySize + ((int)sizeof(int)));
    int offset = offsetBaseValue * (registerToBeRead);

    // Get size of file.
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);

    // Check if offset is surpasing the size.
    if (offset > size)
    {
        printf("Não foi possível ler o arquivo\n");
        return 0;
    }

    // Seek position of element to be read.
    fseek(fp, offset, SEEK_SET);

    fread(p.firstName, sizeof(char), firstNameSize, fp);
    fread(p.lastName, sizeof(char), lastNameSize, fp);
    fread(p.email, sizeof(char), emailSize, fp);
    fread(p.nationality, sizeof(char), nationalitySize, fp);
    fread(&p.age, sizeof(int), 1, fp);
    printFields(&p);

    return 1;
}