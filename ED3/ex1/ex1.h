#ifndef _ex1_
#define _ex1_

#define fileNameSize 51
#define firstNameSize 51
#define lastNameSize 51
#define emailSize 81
#define nationalitySize 51

#define trashChar "$"

typedef struct {
    char firstName[firstNameSize];
    char lastName[lastNameSize];
    char email[emailSize];
    char nationality[nationalitySize];
    int age;

}PESSOA;

// functions.c
void readline(char* string);
void binarioNaTela(char *nomeArquivoBinario);


// IO.c
int readPessoaStdin(PESSOA *p);
int writePessoa(FILE *fp, PESSOA *p);
int readEverything(FILE *fp);
int readRegister(FILE *fp, int registerToBeRead);

#endif 