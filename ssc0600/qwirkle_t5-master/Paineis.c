#include "qwirkle.h"


void PainelInicial() {

    printf("\n         1 - Modo Normal");
    printf("         2 - Modo Cheat\n");
    printf("         >> ");

}


void PainelJogadores(int *njogadores, user **jogador) {

    printf("\33[H\33[2J");

    //pedir a quantidade de usuarios.
    char num_jogadores[20];
    printf("Digite a quantidade de jogadores: ");
    fgets(num_jogadores, 20, stdin); *njogadores = atoi(num_jogadores);

    (*jogador) = (user *) malloc( (*njogadores)*sizeof(user) );
    if((*jogador) == NULL) {printf("Erro ao atribuir memoria para jogaores\n") , exit(0);}


    // pedir o nome de cada um dos jogadores. 
    for(int i = 0; i < (*njogadores); i++) {
        
        printf("Digite o nick do jogador %d: " , (i+1) );
        fgets( ( (*jogador) +i)->nome , 20 , stdin ); 
        //remove '\n'
        int tam = strlen( ( (*jogador) +i)->nome );  ( (*jogador) +i)->nome[tam-1] = '\0';
        
        //setar como zero a quantidade de pontos de cada jogador
        ( (*jogador) + i )->points = 0;
        ( (*jogador) + i )->times_played = 0;
        ( (*jogador) + i )->choice = 0;
        ( (*jogador) + i )->ja_trocou = 0;
        for(int k=0; k<12; k++) {
          ( ( (*jogador) + i )->jogadas_da_vez[k] ) = 42;
        }
    }


}


int PainelPecas() {

    
    printf("----------------------------------------------------------------------------\n");
    printf("             ◆ : a    ◼ : b    ● : c    ★ : d    ✚ : e    ✸ : f             \n");
    printf("  Azul: 1    Branco: 2    Laranja: 3    Roxo: 4    Vermelho: 5    Verde: 6  \n");
    printf("----------------------------------------------------------------------------\n");
    printf("                                  Comandos:                                 \n");
    printf("               jogar peca linha coluna || trocar peca || passar             \n");
    printf("----------------------------------------------------------------------------\n");

    return 0;

}




int PainelPrincipale(user *jogador, int vez_do_jogador, char *pecaTab) {

    printf("----------------------------------------------------------------------------\n");
    printf("                                Vez de: %s                                 \n" , (jogador + vez_do_jogador) ->nome);
    
    PainelPecas();
    printf("  Pecas:            ");
    for(int i=0; i<6; i++) {
        printf("  %s   ", printTab( (jogador + vez_do_jogador)->pecas[i] , pecaTab ) );
    }         
    printf("\n----------------------------------------------------------------------------\n");
    return 0;
}


void PainelPontuacao(user *jogador, int njogadores) {
    for(int i=0; i<njogadores; i++) {
      printf("  Pontuacao de %s: %d\n" , (jogador+i)->nome , (jogador+i)->points );
      // printf("Jogadas inicial e final: [%d %d] [%d %d] [%d %d] [%d %d] [%d %d] [%d %d]\n", (jogador+i)->jogadas_da_vez[0], (jogador+i)->jogadas_da_vez[1], (jogador+i)->jogadas_da_vez[2], (jogador+i)->jogadas_da_vez[3], (jogador+i)->jogadas_da_vez[4], (jogador+i)->jogadas_da_vez[5], (jogador+i)->jogadas_da_vez[6], (jogador+i)->jogadas_da_vez[7], (jogador+i)->jogadas_da_vez[8], (jogador+i)->jogadas_da_vez[9], (jogador+i)->jogadas_da_vez[10], (jogador+i)->jogadas_da_vez[11]);
    }
    printf("----------------------------------------------------------------------------\n");

}


void PainelJogadaInvalida(int valor) {


    if (valor == 0) {
        printf("\n                         ------ACAO INVALIDA--------\n");
    }else if (valor == 7) {
        printf("\n                   ------VOCE NAO POSSUI ESSA PECA--------\n");
    }
}


void PainelVencedor(user *jogador, int njogadores) {
  int temp;
  int biggest = 0;
  char winner[30];

  for(int i=0; i<njogadores; i++) {
    if( (jogador+i)->points > biggest ) {
      biggest = (jogador+i)->points;
      strcmp(winner , (jogador+i)->nome);
    }  
  }

  printf("VENCEDOR COM %d PONTOS: %s\n" , biggest, winner);

}