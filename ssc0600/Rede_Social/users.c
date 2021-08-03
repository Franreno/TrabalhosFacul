#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"rede.h"

void UserNickChecagem(char NickDigitado[]);
int NumeroUsuarios();
int LoginHasSpace(char *login);
void UserCreate(char *comando);
char UserLogin(char *ComparaNome, char *ComparaLogin);



char Users(char *comando, char *UserName, char *UserNick) {



    switch (*comando)
    {

    case('1'):                          // Se o usuário quiz logar
        UserLogin(UserName, UserNick);
        break;

    case('2'):                          // Se o usuário quiz cadastrar um novo perfil
        UserCreate(comando);
        break;

    default:
        break;
    }

    return *UserName, *UserNick;
}




/*
    FUNCAO UserCreate():
    Cria um novo usuario, com o nome e login
    verifica se o login esta disponivel e eh valido
    e adiciona no arquivo .txt de usuarios

*/

void UserCreate(char *comando) {

    char *UserFollowFile;

    FILE *fdin;
    FILE *fucontent;

    struct Usuarios {
        char UserName[50];  //NOME do usuario
        char UserNick[30];      //login do usuario
    };

    struct Usuarios *puser;

    UserFollowFile = (char *) malloc(50 * sizeof(char));
    puser = (struct Usuarios*) malloc(1*sizeof(struct Usuarios));



    //pedir o nome o usuário
    printf("| CADASTRE SEU NOME: ");
    // int pausa; scanf("%d" , &pausa);
    fgets((*puser).UserName, 50, stdin );
    for(int i=0; (*puser).UserName[i] != '\0'; i++) {
        if ((*puser).UserName[i] == '\n') {
            (*puser).UserName[i] = '\0';
        }
    }

    //pedir o login do usuario
    printf("| CADASTRE SEU LOGIN: ");
    fgets( (*puser).UserNick, 30, stdin );
    for(int i=0; (*puser).UserNick[i] != '\0'; i++) {
        if ((*puser).UserNick[i] == '\n') {
            (*puser).UserNick[i] = '\0';
        }
    }


    //checar se ja existe um usuario com o mesmo nick. e checar se ha espacos
    UserNickChecagem((*puser).UserNick);


    //imprime no arquivo o novo usuario
    fdin = fopen("Users.txt" , "a");
    fprintf(fdin, "%s\n", (*puser).UserName);
    fprintf(fdin, "%s\n", (*puser).UserNick);
    fclose(fdin);

    for(int i=0; i < 50; i++) {
        UserFollowFile[i] = '\0';
    }

    strcat(UserFollowFile, "follow_data/");
    strcat(UserFollowFile, puser->UserNick);
    strcat(UserFollowFile, ".txt");

    fdin = fopen(UserFollowFile, "a");

    fclose(fdin);

    user_interface(comando, puser->UserName , puser->UserNick);
}




/*
    FUNCAO UserNickChecagem():
    Essa funcao checa se o login a ser criado pelo usuario ja existe ou nao
    alem disso ela checa se o login digitado contem espacos.

*/

void UserNickChecagem(char *NickDigitado) {

    FILE *fdin;
    fdin = fopen("Users.txt" , "r+");

    if(fdin == NULL) {
        printf("| NAO FOI POSSIVEL ABRIR O ARQUIVO\n");
        exit(0);
    }


    char *temp_name;
    temp_name = (char *) malloc(50*sizeof(char));

    char *temp_login;
    temp_login = (char *) malloc(50*sizeof(char));


    int spaceflag;
    spaceflag = LoginHasSpace(NickDigitado);

    while(spaceflag == 1) {

        PainelInicio();
        printf("|\n|");
        printf("\033[1;31m");
        printf(" INVALIDO. LOGIN NAO PODE SER VAZIO OU CONTER ESPAÇO\n");
        printf("\033[0m");
        printf("| DIGITE OUTRO: ");

        fgets(NickDigitado, 30, stdin);
        for(int i=0; *(NickDigitado+i) != '\0'; i++) {
            if (*(NickDigitado+i) == '\n') {
                (*(NickDigitado+i)) = '\0';
            }
        }
        spaceflag = LoginHasSpace(NickDigitado);
    }



    while( fgets(temp_name, 50, fdin) != NULL ) {
        fscanf(fdin, "%s\n" , temp_login);

        int found = strcmp(temp_login, NickDigitado);

        while(found == 0) {

            PainelInicio();
            printf("|\n|");
            printf("\033[1;31m");
            printf(" LOGIN JA EM USO\n");
            printf("\033[0m");
            printf("| DIGITE OUTRO: ");

            fgets(NickDigitado, 30, stdin);
            for(int i=0; *(NickDigitado+i) != '\0'; i++) {
                if (*(NickDigitado+i) == '\n') {
                    (*(NickDigitado+i)) = '\0';
                }
            }
            
            //faz a verificacao de novo se o login tem espaco ou nao
            spaceflag = LoginHasSpace(NickDigitado);
            while(spaceflag == 1) {

                PainelInicio();
                printf("|\n|");
                printf("\033[1;31m");
                printf(" INVALIDO. LOGIN NAO PODE SER VAZIO OU CONTER ESPAÇO\n");
                printf("\033[0m");
                printf("| DIGITE OUTRO: ");

                fgets(NickDigitado, 30, stdin);
                for(int i=0; *(NickDigitado+i) != '\0'; i++) {
                    if (*(NickDigitado+i) == '\n') {
                    (*(NickDigitado+i)) = '\0';
                    }
                }

                spaceflag = LoginHasSpace(NickDigitado);
            }

            found = strcmp(temp_login, NickDigitado);
            rewind(fdin);
    
        }

    }

    fclose(fdin);
    free(temp_name); free(temp_login);
}




/*
    FUNCAO LoginHasSpace():
    Essa funcao verifica a presenca de espaco no login digitado
    Nao eh pra ter espacos no login, assim a funcao retorna 0 se nao ha espacos
    e retorna 1 se ha espacos

*/

int LoginHasSpace(char *login) {
    int i, flag = 0;
    for(i = 0; *(login + i) != '\0'; i++) {
        if( *(login + i) == ' ') {
            flag = 1;
        }
    }
    if(i == 0){
        flag = 1;
    }
    return flag;
}




/*
    FUNCAO UserLogin():
    Verifica se o login digitado eh existente

    A FAZER... se o login nao for encontrado, apresentar a possibilidade de tentar novamente ou criar um novo usuario
    quando o login for efetuado, mandar o usuario para o painel de usuario
*/

char UserLogin(char *ComparaNome, char *ComparaLogin) {
    int found = -1; //flag pra saber se foi encontrado ou nao

    char *UserLoginInput;
    UserLoginInput = (char *) malloc(30*sizeof(char));


    //verificar se ha um login exatamente igual no arquivos "Users.txt"
    FILE *fdin;
    fdin = fopen("Users.txt" , "r");
    if(fdin == NULL) {
        printf("| ERRO!!\n");
        exit(0);
    }


    while(found != 0) {

        //input do login
        printf("|   Nick de usuário: @");
        printf("\33[0m");
        fgets(UserLoginInput, 30, stdin);

        for(int i=0; *(UserLoginInput+i) != '\0'; i++) {
            if (*(UserLoginInput+i) == '\n') {
                (*(UserLoginInput+i)) = '\0';
            }
        }




        // procura puxando os logins do arquivo "Users.txt"
        while( fgets(ComparaNome, 50, fdin) != NULL ) {
            fscanf(fdin , "%s\n" , ComparaLogin);
            found = strcmp(ComparaLogin, UserLoginInput);
            if (found == 0) {
                break;
            }
        }

        //se strcmp nao retorna 0, significa que nao foi encontrado uma string igual
        if(found != 0) {
            PainelInicio();
            printf("|\n|");
            printf("\033[1;31m");
            printf("   NICK NAO ENCONTRADO!!\tTENTE NOVAMENTE\n");
            printf("\033[0m");

            rewind(fdin);
        }
    }

    fclose(fdin);

    return *ComparaNome , *UserLoginInput; //nome e login do usuario
    free(UserLoginInput);
}
