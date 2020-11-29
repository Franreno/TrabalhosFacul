#include "qwirkle.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {

    //variáveis de modo de jogo e numero de jogadores e infos dos jogadores
    srand(time(0));
    char *game_mode = (char *) malloc(10*sizeof(char));
    user *jogador;

    //variaveis de, respectivamente, comando da jogada, peca, cor da peca, e resetar a cor
    char *comando = (char *) malloc(10*sizeof(char));
    char *peca = (char *) malloc(10*sizeof(char));
    char *color = (char *) malloc(15*sizeof(char));

    int **matrix, valor_da_peca, linha_jogada, coluna_jogada, njogadores;
    int *temp_linha = (int *) malloc(sizeof(int));
    int *temp_coluna = (int *) malloc(sizeof(int));
    int OqueDaVez = -1;
    int cabo = 108;
    char *pecaTab;
    pecaTab = (char *) malloc(sizeof(char) * 25);
    int *matrix_origin = malloc(2*sizeof(int));

    int array_pecas[36] = {11,12,13,14,15,16,21,22,23,24,25,26,31,32,33,34,35,36,41,42,43,44,45,46,51,52,53,54,55,56,61,62,63,64,65,66};
    int garbage_array[256] = {0};

    matrix_origin[0] = 1; matrix_origin[1] = 1;


    PainelJogadores(&njogadores, &jogador);

    PainelInicial();
    fgets(game_mode, 10, stdin);


    int vez_dos_jogadores = 0;   // entre [0, njogaores];
    for(; vez_dos_jogadores<njogadores; vez_dos_jogadores++) {
        NewPieces(array_pecas, &garbage_array, &jogador, vez_dos_jogadores);
    }


    int matrix_rows = 1, matrix_cols = 1;

    matrix = (int**) malloc(matrix_rows*sizeof(int*));
    for(int i = 0; i < matrix_rows; i++) {
        matrix[i] = (int*) malloc(matrix_cols*sizeof(int));
    }


    //contador das vezes que ja foram jogadas
    int contador_geral = 0;
    cabo -= (njogadores*6);
    vez_dos_jogadores = 0;

    //enquando "OqueDaVez != 2, ou seja, enquanto nao passar a vez"
    while(contador_geral != 108) {

        printf("\33[H\33[2J");


        matrix_print(matrix, matrix_rows, matrix_cols, matrix_origin, pecaTab);

        PainelPrincipale(jogador, vez_dos_jogadores, pecaTab);
        PainelPontuacao(jogador, njogadores);

        PainelJogadaInvalida(OqueDaVez);



        //int "OqueDaVez" fala qual foi a acao do jogador -> jogar, trocar ou passar
        OqueDaVez = jogada(matrix, matrix_rows, matrix_cols, matrix_origin, &linha_jogada, &coluna_jogada, &valor_da_peca, &jogador, vez_dos_jogadores, game_mode, &garbage_array, array_pecas, contador_geral, temp_linha, temp_coluna);


        switch (OqueDaVez)
        {
        case (1):
            //falta verificar se a jogada foi valida de acordo com as regras do jogo
            PecaPlacer(&matrix, matrix_origin, linha_jogada, coluna_jogada, valor_da_peca, &jogador, vez_dos_jogadores);
            LastMoveNeedsRealloc(&matrix, &matrix_rows, &matrix_cols, matrix_origin, linha_jogada, coluna_jogada);
            (jogador + vez_dos_jogadores)->times_played++;
            contador_geral++;
            break;

        case (2):
            //passou -> passar a vez..
            pontos(matrix, matrix_origin, linha_jogada, coluna_jogada, &jogador, vez_dos_jogadores, matrix_cols, matrix_rows);
            
            for(int k=0; k<12; k++) {
              (jogador + vez_dos_jogadores)->jogadas_da_vez[k] = 42;
            }

            (jogador + vez_dos_jogadores)->times_played = 0;
            
            (jogador + vez_dos_jogadores)->choice = 0;

            if(vez_dos_jogadores == (njogadores-1) ) {
                RefreshPecas(&jogador, vez_dos_jogadores, array_pecas, &garbage_array);
                vez_dos_jogadores = 0;
            } else {
                RefreshPecas(&jogador, vez_dos_jogadores, array_pecas, &garbage_array);
                vez_dos_jogadores++;
            }
            OqueDaVez = -1;
            break;


        default:
            break;
        }

        if(contador_geral == cabo) {
          contador_geral += (njogadores*6);
        }

    }


    PainelVencedor(jogador, njogadores);

    free(comando); free(peca); free(color); free(game_mode); free(jogador);
    free(matrix); free(pecaTab); free(matrix_origin);
}
