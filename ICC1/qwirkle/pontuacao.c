#include "qwirkle.h"

int pontos(int **matrix, int *matrix_origin, int linha, int coluna, user **jogador, int vez_do_jogador, int matrix_cols, int matrix_rows){

  int i, a, b, pontos_na_jogada = 0, flag;


  if( ((*jogador) + vez_do_jogador)->times_played == 0) {
      return 0;
  }



  // i<12 pois o max eh 12
  for(int i=0; i<12; i+=2) {
    // se o termo par for igual a 42, i+1 tb vai ser 42.
    if( ((*jogador) + vez_do_jogador)->jogadas_da_vez[i] != 42) {
      //linha recebe o valor REAL segundo a origem
      ((*jogador) + vez_do_jogador)->jogadas_da_vez[i] += (matrix_origin[0] -1);
      //coluna recebe o valor REAL segundo a origem
      ((*jogador) + vez_do_jogador)->jogadas_da_vez[i+1] += (matrix_origin[1] -1);
    }

  }
  



  


  if ( ((*jogador) + vez_do_jogador)->jogadas_da_vez[1] == ((*jogador) + vez_do_jogador)->jogadas_da_vez[3] ) {
    i = 0; 
  } else if ( ((*jogador) + vez_do_jogador)->jogadas_da_vez[0] == ((*jogador) + vez_do_jogador)->jogadas_da_vez[2] ) {
    i = 1; 
  }

  // analise da sequencia feita
  if( ( (*jogador) + vez_do_jogador)->times_played == 1) {
    flag = 0;
    // terminar

    a = ((*jogador) + vez_do_jogador)->jogadas_da_vez[0];
    for(b = ((*jogador) + vez_do_jogador)->jogadas_da_vez[1] + 1; matrix[a][b] != 0; b++) {
      flag = 1;
      pontos_na_jogada++;
    }
    for(b = ((*jogador) + vez_do_jogador)->jogadas_da_vez[1] - 1; matrix[a][b] != 0; b--) {
      flag = 1;
      pontos_na_jogada++;
    }

    if(flag == 1) {
      pontos_na_jogada++;
    }

    flag = 0;

    b = ((*jogador) + vez_do_jogador)->jogadas_da_vez[1];
    for(a = ((*jogador) + vez_do_jogador)->jogadas_da_vez[0] + 1; matrix[a][b] != 0; a++) {
      flag = 1;
      pontos_na_jogada++;
    }

      
    for(a = ((*jogador) + vez_do_jogador)->jogadas_da_vez[0] - 1; matrix[a][b] != 0; a--) {
      flag = 1;
      pontos_na_jogada++;
     }

  } else {
    if(i == 1) {
      pontos_na_jogada++;


      a = ((*jogador) + vez_do_jogador)->jogadas_da_vez[0];
      for(b = ((*jogador) + vez_do_jogador)->jogadas_da_vez[1] + 1; matrix[a][b] != 0; b++) {
        pontos_na_jogada++;
      }
      for(b = ((*jogador) + vez_do_jogador)->jogadas_da_vez[1] - 1; matrix[a][b] != 0; b--) {
        pontos_na_jogada++;
      }

    } else if(i == 0) {
      pontos_na_jogada++;

      b = ((*jogador) + vez_do_jogador)->jogadas_da_vez[1];

      for(a = ((*jogador) + vez_do_jogador)->jogadas_da_vez[0] + 1; matrix[a][b] != 0; a++) {
        pontos_na_jogada++;
      }

      
      for(a = ((*jogador) + vez_do_jogador)->jogadas_da_vez[0] - 1; matrix[a][b] != 0; a--) {
        pontos_na_jogada++;
      }

    }

    // verificação de qwirkle
    if(pontos_na_jogada == 6){
      pontos_na_jogada *= 2;

    }

    ( (*jogador) + vez_do_jogador )->points += pontos_na_jogada;
    pontos_na_jogada = 0;

    // analise das perpendiculares
    for(int x = 0; x < ( ((*jogador) + vez_do_jogador)->times_played ); x++) {

      if(i == 0) {
        flag = 0;

        a = ((*jogador) + vez_do_jogador)->jogadas_da_vez[x*2];
        for(b = ((*jogador) + vez_do_jogador)->jogadas_da_vez[x*2+1] + 1; matrix[a][b] != 0; b++) {
          flag = 1;
          pontos_na_jogada++;
        }
        for(b = ((*jogador) + vez_do_jogador)->jogadas_da_vez[x*2+1] - 1; matrix[a][b] != 0; b--) {
          flag = 1;
          pontos_na_jogada++;
        }

        if(flag == 1) {
          pontos_na_jogada++;
        }

      } else if(i == 1) {
        flag = 0;

        b = ((*jogador) + vez_do_jogador)->jogadas_da_vez[x*2+1];
        for(a = ((*jogador) + vez_do_jogador)->jogadas_da_vez[x*2] + 1; matrix[a][b] != 0; a++) {
          flag = 1;
          pontos_na_jogada++;
        }

        a = ((*jogador) + vez_do_jogador)->jogadas_da_vez[x*2] - 1;
     
        for(a = ((*jogador) + vez_do_jogador)->jogadas_da_vez[x*2] - 1; matrix[a][b] != 0; a--) {
          flag = 1;
          pontos_na_jogada++;
        }

        if(flag == 1) {
          pontos_na_jogada++;
        }
      }

    }

  }

  ( (*jogador) + vez_do_jogador )->points += pontos_na_jogada;

  return 1;


}