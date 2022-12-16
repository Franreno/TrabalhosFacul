#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"rede.h"

/*

Arquivo da maioria das funções de painel
    Composições principais da interface da rede

*/






void PainelInicio();





void PainelInicio() {                                   // Painel do menu inicial

    printf("\33[H\33[2J");                              // Limpa a tela


    printf("|-------------------------------------------------------------------------------\n");
    printf("|                               1-Log In  2-Criar Perfil  3-Painel ADM  9-Sair |\n");
    printf("|-------------------------------------------------------------------------------\n|\n|\n|\n|\n");
    printf("|                                     TU&TER\n|\n");
    printf("|                                Seja bem vindo!!!\n|\n|\n|\n|\n");
    printf("|-------------------------------------------------------------------------------\n");

}



void PainelFeedUsuario() {                              // Header para feed do usuário

    printf("\33[H\33[2J");
    printf("|--T&T--------------------------------------------------------------------------\n");
    printf("|    FEED                ENTER-Carregar mais postagens   i-Inicio  0-Novo Post |\n");
    printf("|          1~5-Unfollow  6-Feed Geral  7-Minhas Infos  8-Meus Posts  9-Log Out |\n");
    printf("|-------------------------------------------------------------------------------\n");

}

void PainelFeedGeralUsuario() {                         // Header para feed geral do usuário

    printf("\33[H\33[2J");
    printf("|--T&T--------------------------------------------------------------------------\n");
    printf("|    FEED GERAL          ENTER-Carregar mais postagens   i-Inicio  0-Novo Post |\n");
    printf("| 1~5-Follow/Unfollow  6-Feed Inicial  7-Minhas Infos  8-Meus Posts  9-Log Out |\n");
    printf("|-------------------------------------------------------------------------------\n");

}

void PainelPostsUsuario() {                             // Header para posts do próprio usuário

    printf("\33[H\33[2J");
    printf("|--T&T--------------------------------------------------------------------------\n");
    printf("|    MEUS POSTS          ENTER-Carregar mais postagens   i-Inicio  0-Novo Post |\n");
    printf("|                 1~5-Remover Post  6-Feed Inicial   7-Minhas Infos  9-Log Out |\n");
    printf("|-------------------------------------------------------------------------------\n");

}


void PainelInfoUsuario() {                              // Header das infos do usuário

    printf("\33[H\33[2J");
    printf("|--T&T--------------------------------------------------------------------------\n");
    printf("|    INFORMAÇÕES DO PERFIL                                        ENTER-Voltar |\n");
    printf("|-------------------------------------------------------------------------------\n");

}


void PainelNovaPostagem() {                             // Header de nova postagem

    printf("\33[H\33[2J");
    printf("|--T&T--------------------------------------------------------------------------\n");
    printf("|    NOVA POSTAGEM                                                ENTER-Voltar |\n");
    printf("|-------------------------------------------------------------------------------\n");

}

void PainelFollow(char *login) {                        // Painel noticação de follow

    printf("\33[H\33[2J");
    printf("|--T&T--------------------------------------------------------------------------\n");
    printf("|    USUÁRIO ADICIONADO À LISTA                                   ENTER-Voltar |\n");
    printf("|     - @%s\n", login);
    printf("|-------------------------------------------------------------------------------\n");
    getchar();

}

void PainelUnfollow(char *login) {                      // Painel noticação de unfollow

    printf("\33[H\33[2J");
    printf("|--T&T--------------------------------------------------------------------------\n");
    printf("|    USUÁRIO RETIRADO DA LISTA                                    ENTER-Voltar |\n");
    printf("|     - @%s\n", login);
    printf("|-------------------------------------------------------------------------------\n");
    getchar();

}


void PainelADM() {                                      // Painel de menu inicial do adm

    printf("\33[H\33[2J");

    printf("|-------------------------------------------------------------------------------\n");
    printf("|   1-Usuarios  2-Remover perfil  3-Informacoes da rede  4-Apagar Rede  9-Sair |\n");
    printf("|-------------------------------------------------------------------------------\n|\n|\n|\n|\n");
    printf("|                                     TU&TER\n|\n");
    printf("|                              PAINEL ADMINISTRATIVO\n|\n|\n|\n|\n");           //esse daqui tem q mudar depois
    printf("|-------------------------------------------------------------------------------\n");

}

void PainelADMUsuarios() {                              // Header da lista de usuários da rede

    printf("\33[H\33[2J");
    printf("|--T&T--------------------------------------------------------------------------\n");
    printf("|    USUARIOS DA REDE                                             ENTER-Voltar |\n");
    printf("|-------------------------------------------------------------------------------\n");

}

void PainelADMInformations() {                          //  Header da tela de infos da rede

    printf("\33[H\33[2J");
    printf("|--T&T--------------------------------------------------------------------------\n");
    printf("|    INFORMACOES DA REDE                                          ENTER-Voltar |\n");
    printf("|-------------------------------------------------------------------------------\n");

}



/*
    FUNCAO IsCommandValid():
    verifica se a o comando do painel principal eh valido ou nao
    so ha duas opcoes:
    1 -> login
    2 -> criar novo usuario

*/

void IsCommandValid(char *comando) {
    int tam = 0;
    for(int i=0; *(comando+i) != '\n'; i++) {           // Conta tamanho da sitring
        tam++;
    }

    if(tam != 1) {                                      // String tem que ter tamanho 1
        PainelInicio();                                 // Chama o painel inicial para "refresh de tela" com aviso do erro
        printf("|\n| Comando invalido\n| Digite novamente:\n| >>");
        fgets(comando, 5, stdin);                       // Recolhe o comando
        IsCommandValid(comando);                        // Re-verriica validade do comando
    }
    else {

        if(*comando != '1' && *comando != '2' && *comando != '3' && *comando != '9') {      // E ser um dos caracteres do menu
            PainelInicio();                             // Chama o painel inicial para "refresh de tela" com aviso do erro
            printf("|\n| Comando invalido\n| Digite novamente:\n| >>");
            fgets(comando, 5, stdin);                   // Recolhe o comando
            IsCommandValid(comando);                    // Re-verriica validade do comando
        }

    }
}
