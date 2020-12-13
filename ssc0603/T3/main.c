// fazer um que colocar em ordem
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "T3.h"

int main()
{

    //criacao das variaveis de uso do programa
    int acessos, choice;
    char str[2][32];
    char word_to_translate_complete[32];

    ArvAVL *raiz = cria_ArvAVL();
    FILE *fi;

    fi = fopen("dict.txt" , "r");

    //leitura do dict.txt, dicionario contendo as palavras e acessos.
    while(!feof(fi))
    {
        fscanf(fi , "%d %s %s" , &acessos, str[0], str[1]);
        if(acessos == -1)
            break;
        
        //insercao na arvore AVL.
        insere_ArvAVL(raiz, acessos, str[0] , str[1]);
    }

    fclose(fi);


    //aqui comeca a pegar as escolhas das acoes
    while(choice != -1)
    {
        //pega a escolha, se for -1 acaba.
        scanf(" %d" , &choice);
        if (choice == -1)
            break;
        
        //pega a palavra pra traduzir/completar
        scanf(" %s" , word_to_translate_complete);

        //se for a escolha for 0 ele procura pra traduzir, se for qualquer outro valor ele autocompleta.
        if(choice == 0)
        {
            searchTree(raiz, word_to_translate_complete);
        }
        else
        {
            autocomplete(raiz, choice, word_to_translate_complete);
        }
        
    }
}