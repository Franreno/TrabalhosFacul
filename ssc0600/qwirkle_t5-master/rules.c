#include "qwirkle.h"

int game_way(int **matrix, int *matrix_origin, int matrix_rows, int matrix_cols, int *linha, int *coluna, int *peca) {
    int i = *linha + matrix_origin[0] - 1;
    int j = *coluna + matrix_origin[1] - 1;
    int gw = 0; // Gameway -> 1 para sequencia de cor, 2 para sequencia de forma
    //Possiveis erros > Fim da matriz ou inicio


    //Horizontal p/ direita
    int a = i;
    for(int b = j;  b != matrix_cols - 1 && matrix[a][b + 1] != 0; b++){

      if(matrix[a][b + 1] == *peca){
        return 0;

      } else if(((matrix[a][b + 1] % 10) ==  (*peca % 10)) && gw != 2) { // mesma cor
        gw = 1;

      } else if((abs(matrix[a][b + 1] - *peca) <= 5) && gw != 1) { // mesma forma
        gw = 2; 

      } else {
        return 0;
      }
    }

    


    for(int b = j;  b != 0 && matrix[a][b - 1] != 0 ; b--){

      if(matrix[a][b - 1] == *peca){
        return 0;

      } else if(((matrix[a][b - 1] % 10) ==  (*peca % 10)) && gw != 2) { // mesma cor
        gw = 1;

      } else if((abs(matrix[a][b - 1] - *peca) <= 5) && gw != 1) { // mesma forma
        gw = 2;

      } else {
        return 0;
      }
    }


    gw = 0;

    int b = j;
    for(int a = i; a != matrix_rows - 1 && matrix[a + 1][b] != 0; a++){

      if(matrix[a + 1][b] == *peca){
        return 0;

      } else if(((matrix[a + 1][b] % 10) ==  (*peca % 10)) && gw != 2) { // mesma cor
        gw = 1;

      } else if((abs(matrix[a + 1][b] - *peca) <= 5) && gw != 1) { // mesma forma
        gw = 2;

      } else {
        return 0;
      }
    }


    for(int a = i; a != 0 && matrix[a - 1][b] != 0; a--){

      if(matrix[a - 1][b] == *peca){
        return 0;
      } else if(((matrix[a - 1][b] % 10) ==  (*peca % 10)) && gw != 2) { // mesma cor
        gw = 1;

      } else if((abs(matrix[a - 1][b] - *peca) <= 5) && gw != 1) { // mesma forma
        gw = 2;

      } else {
        return 0;
      }
    }


 
  return 1;

}



int same_seq(int flag, int *linha, int *coluna, int *temp_linha, int *temp_coluna, user **jogador, int vez_do_jogador, int **matrix, int *matrix_origin) {

    // ((*jogador) + vez_do_jogador)->choice;

    if( ( (*jogador) + vez_do_jogador)->times_played == 0 ){
        *temp_linha = *linha;
        *temp_coluna = *coluna;
        
    }
    else{
        if(*temp_linha != *linha && *temp_coluna != *coluna){
            return 0;
        }
        else{
            if(*temp_linha == *linha){
                if(((*jogador) + vez_do_jogador)->choice == 2){
                    return 0;
                }
                else{
                ((*jogador) + vez_do_jogador)->choice = 1;
                }
            }
            else{
                if(((*jogador) + vez_do_jogador)->choice == 1){
                    return 0;
                }
                else{
                    ((*jogador) + vez_do_jogador)->choice = 2;
                }
            }
        }   
    }
    int flag_null;
    flag_null = isNull( ((*jogador) + vez_do_jogador)->choice, (*temp_linha) + matrix_origin[0] - 1, (*temp_coluna) + matrix_origin[1] - 1, (*linha) + matrix_origin[0] - 1, (*coluna) + matrix_origin[1] - 1, matrix);

    if(flag_null == 0) {
      return 0;
    }


    return 1;
}

int isNull(int escolha, int linha_origem, int coluna_origem, int nova_linha, int nova_coluna, int **matrix){
//Escolha 1 > mesma linha, coluna varia

if(escolha == 1){

  if(coluna_origem > nova_coluna){
    for(nova_coluna = nova_coluna + 1; nova_coluna < coluna_origem; nova_coluna++){
      if(matrix[linha_origem][nova_coluna] == 0){
        return 0;
      }
    }
  }
  else{
    for(nova_coluna = nova_coluna - 1; nova_coluna > coluna_origem; nova_coluna--){
      if(matrix[linha_origem][nova_coluna] == 0){
        return 0;
      }
    }
  }
  return 1;
  }
//Choice 2
  else{
    if(linha_origem > nova_linha){
      for(nova_linha = nova_linha + 1; nova_linha < linha_origem; nova_linha++){
        if(matrix[nova_linha][coluna_origem] == 0){
        
          return 0;
        }
      }
    } 
    else{
      for(nova_linha = nova_linha - 1; nova_linha > linha_origem; nova_linha--){
        if(matrix[nova_linha][coluna_origem] == 0){
          
          return 0;
        }
      }
    }
    return 1;
  }



  return 1;

  }











int away(int **matrix, int *matrix_origin, int *linha, int *coluna, int matrix_cols, int matrix_rows) {
    int i = ( (*linha) + matrix_origin[0] - 1);
    int j = ( (*coluna) + matrix_origin[1] - 1);
    int contador = 0;

    if(i != matrix_rows - 1){
        if(matrix[i + 1][j] == 0){
        contador++;
    }
    }

    if(i == matrix_rows - 1){
        contador++;
    }

    if(i != 0){
        if(matrix[i - 1][j] == 0){
        contador++;
    }
    }

    if(i == 0){
        contador++;
    }

    if(j != matrix_cols - 1){
        if(matrix[i][j + 1] == 0){
        contador++;
    }
    }

    if(j == matrix_cols - 1){
        contador++;
    }

    if(j != 0){
    if(matrix[i][j - 1] == 0){
        contador++;
    }
    }



    if(j == 0){

        contador++;
    }

    if(contador == 4){
        return 0;
    }


    return 1;
    //verificar se a pessoa nao jogou em um lugar "away" no tabuleiro, ja que as outras funções desconsideram o "0"
    //possivel erro > nao pode ser aplicada na primeira jogada
}








int AllTheRules(int **matrix, int *matrix_origin, int matrix_cols, int matrix_rows, int contador_geral, int *linha, int *coluna, int *temp_linha, int *temp_coluna, user **jogador, int vez_do_jogador, int *valor_da_peca) {
    int flag_rules = 0;

        flag_rules = away(matrix, matrix_origin, linha, coluna, matrix_cols, matrix_rows);

        if(flag_rules == 0) {
            return flag_rules;
        }

        
        flag_rules = game_way(matrix, matrix_origin, matrix_rows,matrix_cols, linha, coluna, valor_da_peca);
    
        if(flag_rules == 0) {
            return flag_rules;
        }


        flag_rules = same_seq(contador_geral, linha, coluna, temp_linha, temp_coluna, jogador, vez_do_jogador, matrix, matrix_origin);

          
        if(flag_rules == 0) {
            return flag_rules;
        }
        

    return flag_rules;
} 








