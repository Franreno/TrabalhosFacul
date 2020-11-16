#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvBin.h"

int main() 
{
    //receber os valores de input ate encontrar 3 x
    char str[3][512];

    ArvBin* raiz = criaArvBin();

	// enquanto os 3 valores das strings forem diferentes de X
    while (str[0][0] != 'X' || str[1][0] != 'X' || str[2][0] != 'X')
    {
        scanf("%s %s %s" , str[0] , str[1] , str[2]);

		//ciclo pra inserir na arvore
        for (int i=0; i<3; i++)
        {
			// so nao insere se for um X
            if( str[i][0] != 'X' )
                insertBinaryTree(raiz, str[i], i, str[0]);
        }
    }

	//A saida pedida pelo trabalho
    mostraArvBin(raiz);

	//liberar os nodulos e a raiz
    liberaArvBin(raiz);

    return 0;
}
