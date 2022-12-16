#include "qwirkle.h"
#include <stdio.h>

int SymbolConverter(char peca[]);
int FuncaoJogar(int **matrix, int matrix_rows, int matrix_cols, int *matrix_origin, char peca[], int *linha, int  *coluna, int *valor_da_peca, user **jogador, int vez_do_jogador, char *game_mode);
int WasMoveValid(int **matrix, int matrix_rows, int matrix_cols, int *matrix_origin, int *linha, int *coluna);
int DoesPlayerHasPiece(user **jogador, int vez_do_jogador, int *valor_da_peca);
int BoraTrocar(int (*garbage_array)[], int array_pecas[], user **jogador, int vez_do_jogador, int *value, char peca[]);

int jogada(int **matrix, int matrix_rows, int matrix_cols, int *matrix_origin, int *linha, int  *coluna, int *valor_da_peca, user **jogador, int vez_do_jogador, char *game_mode, int (*garbage_array)[], int array_pecas[], int contador_geral, int *temp_linha, int *temp_coluna) {

   char acao[20], player[20], peca[20];


    int flag_geral = 0;

    printf("\nInput:\n >>");
    scanf("%s", acao);

    if(strncmp(acao, "jogar", 20) == 0){

        // if( ( (*jogador) + vez_do_jogador )->ja_trocou != 0) {
        //     printf("entrei?\n"); 
        //     flag_geral = 9;
        //     return flag_geral;
        // }


        flag_geral = FuncaoJogar(matrix, matrix_rows, matrix_cols, matrix_origin, peca, linha, coluna, valor_da_peca, jogador, vez_do_jogador, game_mode);

        if(flag_geral == 0 || flag_geral == 7) {
            return flag_geral;
        }


        if(contador_geral > 0) {

            flag_geral = AllTheRules(matrix, matrix_origin, matrix_cols, matrix_rows, contador_geral, linha, coluna, temp_linha, temp_coluna, jogador, vez_do_jogador, valor_da_peca);

        }

    } else if ( strncmp(acao, "passar", 20) == 0 ) {
        flag_geral = 2;

    } else if (strncmp(acao, "trocar", 20) == 0) {
        
        if ( ( (*jogador) + vez_do_jogador )->ja_trocou != 6 ) {
            flag_geral = BoraTrocar(garbage_array, array_pecas, jogador, vez_do_jogador, valor_da_peca, peca);
        }

    }

    return flag_geral;
}

int FuncaoJogar(int **matrix, int matrix_rows, int matrix_cols, int *matrix_origin, char peca[], int *linha, int  *coluna, int *valor_da_peca, user **jogador, int vez_do_jogador, char *game_mode) {

    int flag_jogar = 0;

    scanf("%s %d %d", peca, linha, coluna);
    *valor_da_peca = SymbolConverter(peca);


    if (*valor_da_peca == 0) {
        return flag_jogar;
    }

    flag_jogar = WasMoveValid(matrix, matrix_rows, matrix_cols, matrix_origin, linha, coluna);
    if(flag_jogar == 0) {
        return 0;
    }

    // Fazer essa verificacao somente se o modo de jogo for livre
    if( strcmp(game_mode, "1\n") == 0 ) {
        flag_jogar = DoesPlayerHasPiece(jogador, vez_do_jogador, valor_da_peca);
    }

    return flag_jogar;
}



//converter a peca a1 pra seu valor int segundo os seus valores.
int SymbolConverter(char peca[]) {
    //primeira posicao da string peca eh o formato, segunda posicao eh a cor

    int pecafinal = 0;
    switch ( peca[0] )
    {
    case ('a'):
        pecafinal = 10;
        break;

    case ('b'):
        pecafinal = 20;
        break;

    case ('c'):
        pecafinal = 30;
        break;

    case ('d'):
        pecafinal = 40;
        break;

    case ('e'):
        pecafinal = 50;
        break;

    case ('f'):
        pecafinal = 60;
        break;

    default:
        printf("Valor da peca invalido\n");
        return 0;
        break;
    }


    switch ( peca[1] )
    {
    case ('1'):
        pecafinal += 1;
        break;

    case ('2'):
        pecafinal += 2;
        break;

    case ('3'):
        pecafinal += 3;
        break;

    case ('4'):
        pecafinal += 4;
        break;

    case ('5'):
        pecafinal += 5;
        break;

    case ('6'):
        pecafinal += 6;
        break;

    default:
        printf("Valor da peca Invalido!\n");
        return 0;
        break;
    }

    return pecafinal;
}


int WasMoveValid(int **matrix, int matrix_rows, int matrix_cols, int *matrix_origin, int *linha, int *coluna) {



    if( (*linha + matrix_origin[0]) > matrix_rows) {

        return 0;

    } else if ( (*coluna + matrix_origin[1])   > matrix_cols) {


        return 0;

    }if( (*linha + matrix_origin[0] ) -1 < 0) {

        return 0;

    } else if ( (*coluna + matrix_origin[1]) -1  < 0) {

        return 0;

    } else if( (matrix)[ (*linha + matrix_origin[0])-1 ][ (*coluna + matrix_origin[1])-1 ] != 0 ) {

        return 0;
    }

    return 1;
}

int DoesPlayerHasPiece(user **jogador, int vez_do_jogador, int *valor_da_peca) {

    // Se for encontrado a peca dentro do array de pecas do jogador, a jogada eh valida
    for(int i=0; i<6; i++) {
        if ( ( (*jogador) + vez_do_jogador )->pecas[i]  == *valor_da_peca ) {
            return 1;
        }
    }

    return 7;
}

int PecaPlacer(int ***matrix, int *matrix_origin, int linha, int coluna, int valor_da_peca, user **jogador, int vez_do_jogador) {

    // Colocar a peca q foi jogada no tabuleiro.
    (*matrix)[ (linha + matrix_origin[0])-1 ][ (coluna + matrix_origin[1])-1 ] = valor_da_peca;

    //retirar a peca do vetor de pecas da pessoa.
    for(int i=0; i<6; i++) {
        if ( ( (*jogador) + vez_do_jogador)->pecas[i] == valor_da_peca ) {
            ( (*jogador) + vez_do_jogador)->pecas[i] = -1;
            break;
        }
    }
  

    int k = ((*jogador) + vez_do_jogador )->times_played;
    ( (*jogador) + vez_do_jogador)->jogadas_da_vez[2*k] =  linha;
    ( (*jogador) + vez_do_jogador)->jogadas_da_vez[2*k+1] = coluna;


    return 0;
}



int LastMoveNeedsRealloc(int ***matrix, int *matrix_rows, int *matrix_cols, int *matrix_origin, int linha, int coluna) {

    int flag_linha = -1, flag_coluna = -1, flag_final = -1;

    /*
        linha precisa aumentar pra cima, flag_linha = 1
        linha precisa aumentar pra baixo, flag_linha = 0
        linha nao precisa aumentar, flag_linha = -1

        coluna precisa aumentar pra direita, flag_coluna = 1
        coluna precisa aumentar pra esquerda, flag_coluna = 0
        coluna nao precisa aumentar, flag_coluna = -1
    */

    // verificar se a ultima jogada foi feita nas bordas da matriz atual..
    // (linha + matrix_origin[0]) -1; (coluna + matrix_origin[1]) -1;

    if( ( (linha + matrix_origin[0])  ) == (*matrix_rows) ) {
        // aumentar pra baixo
        flag_linha = 0;
    } else if ( ( (linha + matrix_origin[0]) -1 ) == 0) {
        //aumentar pra cima
        flag_linha = 1;
    }

    if ( ( (coluna + matrix_origin[1])  )  == (*matrix_cols) ) {
        //aumentar pra direita
        flag_coluna = 1;
    } else if ( ( (coluna + matrix_origin[1]) -1 ) == 0) {
        //aumentar pra esquerda
        flag_coluna = 0;
    }


    /*  possibilidaes:
        aumentar so uma linha pra cima                                              flag_final == 1   flag_linha = 1   flag_coluna = -1
        aumentar so uma linha pra baixo (max rows)                                  flag_final == 2   flag_linha = 0   flag_coluna = -1
        aumentar so uma coluna para a direita                                       flag_final == 3   flag_linha = -1  flag_coluna = 1
        aumentar so uma coluna para a esquerda                                      flag_final == 4   flag_linha = -1  flag_coluna = 0
        aumentar uma linha e coluna, linha pra baixo, coluna pra esquerda           flag_final == 5   flag_linha = 0   flag_coluna = 0
        aumentar uma linha e coluna, linha pra cima, coluna para a esquerda         flag_final == 6   flag_linha = 1   flag_coluna = 0
        aumentar uma linha e coluna, linha pra baixo, coluna para a direita         flag_final == 7   flag_linha = 0   flag_coluna = 1
        aumentar uma linha e coluna, linha pra cima, coluna para a direita          flag_final == 8   flag_linha = 1   flag_coluna = 1
        aumentar uma linha ou coluna para todos os lados                            flag_final == 9
        nao precisa aumentar                                                        flag_final == -1  flag_linha = -1  flag_coluna = -1
    */


   if (*matrix_cols == 1 && *matrix_rows == 1) {
       flag_final = 9;

   } else if ( flag_linha == -1 && flag_coluna == -1 ) {
       flag_final = -1;

   } else if ( flag_linha == 1 && flag_coluna == -1 ) {
       flag_final = 1;

   } else if ( flag_linha == 0 && flag_coluna == -1 ) {
       flag_final = 2;

   } else if ( flag_linha == -1 && flag_coluna == 1 ) {
       flag_final = 3;

   } else if ( flag_linha == -1 && flag_coluna == 0 ) {
       flag_final = 4;

   } else if ( flag_linha == 0 && flag_coluna == 0 ) {
       flag_final = 5;

   } else if ( flag_linha == 1 && flag_coluna == 0 ) {
       flag_final = 6;

   } else if ( flag_linha == 0 && flag_coluna == 1 ) {
       flag_final = 7;

   } else if ( flag_linha == 1 && flag_coluna == 1 ) {
       flag_final = 8;
   }

    SwitchRealloc(matrix, matrix_rows, matrix_cols, matrix_origin, flag_final);
    return 0;
}

int SwitchRealloc(int ***matrix, int *matrix_rows, int *matrix_cols, int *matrix_origin, int flag_realloc) {

     /*  possibilidaes:
        aumentar so uma linha pra cima                                              flag_realloc == 1  add_row = -1   add_col =  0
        aumentar so uma linha pra baixo (max rows)                                  flag_realloc == 2  add_row =  1   add_col =  0
        aumentar so uma coluna para a direita                                       flag_realloc == 3  add_row =  0   add_col =  1
        aumentar so uma coluna para a esquerda                                      flag_realloc == 4  add_row =  0   add_col = -1
        aumentar uma linha e coluna, linha pra baixo, coluna pra esquerda           flag_realloc == 5  add_row =  1   add_col = -1
        aumentar uma linha e coluna, linha pra cima, coluna para a esquerda         flag_realloc == 6  add_row = -1   add_col = -1
        aumentar uma linha e coluna, linha pra baixo, coluna para a direita         flag_realloc == 7  add_row =  1   add_col =  1
        aumentar uma linha e coluna, linha pra cima, coluna para a direita          flag_realloc == 8  add_row = -1   add_col =  1
        aumentar uma linha ou coluna para todos os lados                            flag_realloc == 9
        nao precisa aumentar                                                        flag_realloc == -1
    */

   switch (flag_realloc)
   {
    case (1):
       ReallocMatrix(matrix, matrix_rows, matrix_cols, matrix_origin, -1 , 0);
       break;

    case (2):
       ReallocMatrix(matrix, matrix_rows, matrix_cols, matrix_origin, 1 , 0);
       break;

    case (3):
       ReallocMatrix(matrix, matrix_rows, matrix_cols, matrix_origin, 0 , 1);
       break;

    case (4):
       ReallocMatrix(matrix, matrix_rows, matrix_cols, matrix_origin, 0 , -1);
       break;

    case (5):
       ReallocMatrix(matrix, matrix_rows, matrix_cols, matrix_origin, 1 , -1);
       break;

    case (6):
       ReallocMatrix(matrix, matrix_rows, matrix_cols, matrix_origin, -1 , -1);
       break;

    case (7):
       ReallocMatrix(matrix, matrix_rows, matrix_cols, matrix_origin, 1 , 1);
       break;

    case (8):
       ReallocMatrix(matrix, matrix_rows, matrix_cols, matrix_origin, -1 , 1);
       break;

    case (9):
       ReallocMatrix(matrix, matrix_rows, matrix_cols, matrix_origin, -1 , -1);
       ReallocMatrix(matrix, matrix_rows, matrix_cols, matrix_origin, 1 , 1);

   default:
       break;
   }

   return 0;
}



// Funcao para realizar a troca de uma peca
int BoraTrocar(int (*garbage_array)[], int array_pecas[], user **jogador, int vez_do_jogador, int *value, char peca[]) {
    int flag_trocar = 0;

    //sintaxe: trocar (*peca)

    scanf("%s" , peca);

    *value = SymbolConverter(peca);
    if(*value == 0) {
        return flag_trocar;
    }

    flag_trocar = TrocaPeca(garbage_array, array_pecas, jogador, vez_do_jogador, value);


    return flag_trocar;
}
