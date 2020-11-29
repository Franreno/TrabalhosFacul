#include <stdio.h>
#include <stdlib.h>
#include "rede.h"


/*
    main: funcao onde tudo comeca.
*/


int main() {


    char *comando; char *UserName; char *UserNick;
    comando = (char *) malloc(5 * sizeof(char));
    UserName = (char *) malloc(50 * sizeof(char));
    UserNick = (char *) malloc(30 * sizeof(char));


    while(*comando != '9') {

        PainelInicio();                                     // Chama função do painel de início
        printf("|\n|   >>  ");
        fgets(comando, 5, stdin);                           // Ação inícial do usuário
        IsCommandValid(comando);                            // Verifica validade da ação

        switch (*comando)
        {
        case ('1'):
            Users(comando, UserName, UserNick);
            user_interface(comando, UserName, UserNick);
            break;

        case('2'):
            Users(comando, UserName, UserNick);
            break;

        case('9'):
            break;

        case('3'):
            adm_interface(comando, UserName, UserNick);
            break;

        default:
            break;
        }
    }

    printf("\33[H\33[2J");


    free(UserName); free(UserNick); free(comando);      // Memorias alocadas são liberadas

}
