// fazer um que colocar em ordem
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "T3.h"

int main()
{
    int acessos;
    char str[2][32];
    ArvAVL *raiz = cria_ArvAVL();
    FILE *fi;
    fi = fopen("dict.txt" , "r");

    while(!feof(fi))
    {
        fscanf(fi , "%d %s %s" , &acessos, str[0], str[1]);
        if(acessos == -1)
            break;
        
        insere_ArvAVL(raiz, acessos, str[0] , str[1]);
    }

    fclose(fi);


    int choice;
    char word_to_translate_complete[32];

    while(choice != -1)
    {

        scanf(" %d" , &choice);
        if (choice == -1)
            break;
        
        scanf(" %s" , word_to_translate_complete);

        if(choice == 0)
        {
            searchTree(raiz, word_to_translate_complete);
        }
        else
        {
            printf("entrei no autocomplete\n");
            //autocomplete
        }
        

    }
}