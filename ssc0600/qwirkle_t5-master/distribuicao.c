#include "qwirkle.h"

int TrashTime(int value, int (*garbage_array)[]);


// Distribui novas pecas para os jogadores. esse eh para a primeira vez q ta colocando as pecas
int NewPieces(int array_pecas[], int (*garbage_array)[], user **jogador, int vez_do_jogador) {



    int j, trash_flag = 0;
    for(int i=0; i<6; i++) {
        // verificar a existencia dessa peca no vetor garbage_array, se tiver >4 pecas iguais nele nao deixar


        while(trash_flag == 0) {
            j = ( rand() % 36 );
            trash_flag = TrashTime(array_pecas[j], garbage_array);
        }



        ( (*jogador) + vez_do_jogador )->pecas[i] = array_pecas[j];

        trash_flag = 0;


    }

    return 0;
}


// verificar se ha >4 pecas no vetor lixo, vetor das pecas q ja foram atribuidas
int TrashTime(int value, int (*garbage_array)[]) {
    
    int contador = 0;

    for(int i=0; i<256; i++) {

        // contando a quantidade de vez q a peca aparece nesse vetor
        // ou seja a qnt de vezes que ela ja foi usada
        if((*garbage_array)[i] == value) {
            contador++;
        }

        //so pode existir 3 pecas de cada dentro do jogo
        if(contador == 3) {
            return 0;
        }

    }
    
    //ja adiciona o novo valor da peca no array de lixo
    for(int i=0; i<256; i++) {
        if( (*garbage_array)[i] == 0) {
            (*garbage_array)[i] = value;
            break;
        }
    }

    return 1;
}


int TrocaPeca(int (*garbage_array)[], int array_pecas[], user **jogador, int vez_do_jogador, int *value) {
    
    if (DoesPlayerHasPiece(jogador, vez_do_jogador, value) == 7) {
        return 7;
    }

    //tirar uma dessa peca do vetor lixo
    for(int i=0; i<256; i++) {
        if( (*garbage_array)[i] == (*value) ) {
            (*garbage_array)[i] = 0;
            break;
        }
    }

    //tirar essa peca do vetor da pessoa e colocar uma nova
    int aleatorio;
    int flag_trash = 0;

    // ate encontrar uma peca valida!
    while(flag_trash == 0) {
        
        aleatorio = ( rand() % 36 );
        flag_trash = TrashTime(array_pecas[aleatorio] , garbage_array);

    }


    //substitui o valor da peca no vetor de pecas do jogador
    for(int i=0; i<6; i++) {
        if ( ( (*jogador) + vez_do_jogador )->pecas[i] == (*value) ) {
            ( (*jogador) + vez_do_jogador )->pecas[i] = array_pecas[aleatorio];
            break;
        }
    }

    ( (*jogador) + vez_do_jogador )->ja_trocou++;
    //valor de retorno para o trocar
    return 3;
}


// Funcao pra dar novas pecas aos usuarios depois de terem passado a vez
int RefreshPecas (user **jogador, int vez_do_jogador, int array_pecas[], int (*garbage_array)[]) {
    
    int aleatorio;
    int flag_refresh = 0;
    // int cabo = 108 - (njogadores*6);

    // if(*contador_geral == cabo) {
    //   *contador_geral = (*contador_geral) + (njogadores*6);
    //   return 0;
    // }




    for(int i=0; i<6; i++) {

        // depois de ter jogado, a posicao do vetor do jogador fica como -1
        // entao, se encontrado o -1 no vetor, tem q colocar alguma outra peca nele

        if( ( (*jogador) + vez_do_jogador)->pecas[i] == -1 ) {
            //colocar nova peca nessa posicao


            // faz a verificacao se a peca ainda continua valida
            while(flag_refresh == 0) {
                aleatorio = ( rand() % 36 );
                flag_refresh = TrashTime(array_pecas[aleatorio] , garbage_array);
            }

            flag_refresh = 0;

            //manda a peca pro vetor
            ( (*jogador) + vez_do_jogador)->pecas[i] = array_pecas[aleatorio];
        }
    }

    return 0;
}