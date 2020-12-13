// fazer um que colocar em ordem
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "T3.h"

int manualatoi(char s[32])
{
    if( strcmp(s , "-1\n") == 0 )
        return -1;
    else if( strcmp(s , "0\n" ) == 0 )
        return 0;
    else
        return 1;
}


int main()
{
    char acessos[10];
    int acessos2;
    char str[2][32];
    ArvAVL* raiz = cria_ArvAVL();
    FILE *fi;
    fi = fopen("dict.txt" , "r");

    while( !feof(fi) )
    {
        fgets(acessos, 10 , fi);
        if( strcmp(acessos, "-1") == 0)
            break;
        fgets(str[0] , 32 , fi);
        fgets(str[1] , 32 , fi);
        
        int len1 = strlen(str[0]);
        int len2 = strlen(str[1]);
        str[0][len1-1] = '\0';
        str[1][len2-1] = '\0';

        // printf("%s%s%s" , acessos, str[0] , str[1]);

        acessos2 = manualatoi(acessos);
        insere_ArvAVL(raiz, acessos2, str[0] , str[1]);
    }

    char choice[10];
    char word_to_translate_complete[32];

    fgets(choice, 10 , stdin);
    int choice2 = manualatoi(choice);

    while( choice2 != -1 )
    {
        fgets(word_to_translate_complete, 32, stdin);
        int len3 = strlen(word_to_translate_complete);
        word_to_translate_complete[len3-1] = '\0';

        if (choice2 == 0)
        {
            searchTree(raiz, word_to_translate_complete);
        }
        else
        {
            printf("entrei no else\n");
            //autocomplete
        }

        fgets(choice, 10, stdin);
        choice2 = manualatoi(choice);   
    }




    // int acessos;
    // char str[2][32];
    // ArvAVL* raiz = cria_ArvAVL();
    // FILE *fi;
    // fi = fopen("dict.txt" , "r");
    
    // while( !feof(fi) )
    // {
    //     fscanf(fi , "%d\n%s\n%s\n" , &acessos, str[0] , str[1]);
    //     if(acessos == -1)
    //         break;

    //     insere_ArvAVL( raiz, acessos, str[0] , str[1] ); 
    // }


    // emOrdem_ArvAVL(raiz);

    // // while(acessos != -1)
    // // {
    // //     scanf("%d\n " , &acessos);
    // //     scanf("%s\n" , str[0]  );
    // //     scanf("%s\n" , str[1]  );
    // // }

    // int choice;
    // char word_to_translate_complete[32];


    // while(choice != -1)
    // {
    //     scanf("%d\n%s" , &choice, word_to_translate_complete);
    //     printf("aosidjfn\n");

    //     if(choice == 0)
    //     {
    //         printf("entrei?\n");
    //         searchTree(raiz, word_to_translate_complete);
    //     }
    //     else
    //     {
    //         //autocomplete
    //     }


    //     scanf("%d " , &choice);
    // }
}