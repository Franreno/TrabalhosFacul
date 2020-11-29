#include "lde.h"


/*
    Funcao pegastr
        Funcao de input da string a ser criptografada
*/
int pegastr(List *start, char str[])
{
    fgets(str, 1024, stdin);

    for (int i = 0; str[i] != '\n'; i++)
    {
        // Cada caractere eh inserido individualmente na lista utilizando a funcao InsereFim.
        InsereFim(start, str[i]);
    }
}

/*
    Funcao switchpegachave
        Funcao que converte um char (48 - 57) em seu correspondente numerico (0 - 9)
*/
int switchpegachave(char c) 
{
    switch (c)
    {
    case 48:
        return 0;
        break;

    case 49:
        return 1;
        break;
    
    case 50:
        return 2;
        break;
    
    case 51:
        return 3;
        break;

    case 52:
        return 4;
        break;

    case 53:
        return 5;
        break;        

    case 54:
        return 6;
        break;

    case 55:
        return 7;
        break;

    case 56:
        return 8;
        break;

    case 57:
        return 9;
        break;

    default:
        return -1;
        break;
    }

    return -1;
}


/*
    Funcao *pegachave
        Funcao que recebe o input do usuario para a chave numerica
        A string da chave eh convertida em valor numerico pela funcao switchpegachave
        E cada valor numerico eh colocado individualmente em um array
        Por fim, a funcao retorna esse array.
*/
int *pegachave(int *auxvector)
{
    char chave[256];
    fgets(chave, 256, stdin);
    int len = strlen(chave);
    chave[len-1] = '\0';

    int count=0;
    for(int i=0; i<len; i++)
    {
        auxvector[i] = switchpegachave(chave[i]);
        count = i;
    }
    auxvector[count+1] = -1;

    return auxvector;
}


/*
    Funcao keysize
        Retorna o tamanho do array da chave de encriptacao
*/
int keysize(int *key)
{
    int count = 0;
    for(int i=0; i<256; i++)
    {
        if(key[i] == -1)
            break;
        else
        {
            count++;
        }
    }

    return count;
}



int main()
{
    // Declaracao das variaveis iniciais.
    char str[1024];
    int *key = (int *)calloc(256 , sizeof(int));
    int k_size;

    // Criacao da lista
    List *start = CriaLista();

    int option;
    scanf("%d ", &option);


    // Switch case pras opcoes de encriptacao possiveis.
    switch (option)
    {
    case 1:
        pegastr(start, str);
        Option1(start);
        break;

    case -1:
        pegastr(start, str);
        Option_1(start);
        break;

    case 2:
        pegastr(start, str);
        Option2(start);
        break;

    case -2:
        pegastr(start, str);
        Option_2(start);
        break;

    case 3:
        pegastr(start, str);
        Option3(start);
        break;

    case -3:
        pegastr(start, str);
        Option_3(start);
        break;

    case 4:
        pegachave(key);
        k_size = keysize(key);
        pegastr(start, str);
        Option4(start, key, k_size);
        break;

    case -4:
        pegachave(key);
        k_size = keysize(key);
        pegastr(start, str);
        Option_4(start, key, k_size);
        break;

    case 5:
        pegachave(key);
        k_size = keysize(key);
        pegastr(start, str);
        Option5(start, key, k_size);
        break;

    case -5:
        pegachave(key);
        k_size = keysize(key);
        pegastr(start, str);
        Option_5(start, key, k_size);
        break;

    default:
        break;
    }

    // Imprime a lista nodulo por nodulo.
    display(start);
    printf("\n");

    // Libera a memoria da lista e do array numerico.
    DeleteList(start);
    free(key);
}