// fazer um que colocar em ordem
#include <stdio.h>
#include <string.h>
#include "T3.h"


int main()
{
    int acessos;
    char str[2][32];
    ArvAVL* raiz = cria_ArvAVL();

    
    while(acessos != -1)
    {
        printf("entrei\n Digite acessos: ");
        scanf("%d\n " , &acessos);
        
        if (acessos == -1)
            break;
        
        fflush(stdin);
        printf("digite str1: ");
        scanf(" %s\n" , str[0]  );
        printf("digite str2: ");
        scanf("%s\n" , str[1]  );
        
        insere_ArvAVL( raiz, acessos, str[0] , str[1] );    
    }

    printf("sai\n");

    int choice;

    char word_to_translate_complete[32];

    while(choice != -1)
    {
        scanf("%d\n" , &choice);

        scanf("%s\n" , word_to_translate_complete);
        
        if(choice == 0)
            searchTree(raiz, word_to_translate_complete);
        else if(choice == 1)
        {
            //autocomplete
        }
    }


    //consultarv()

    // scanf("%s %s" , str[0], str[1]);

    // organizar elas em ordem alfabetica.
    // int flag;
    // flag = alfabetical(str);
    
    // printStringsInOrder(str, flag);
        
}