#include "lde.h"

/*
    Funcao Option1
        Cada caracatere da lista recebe +1, em relacao ao seu valor ASCII
*/
int Option1(List *start)
{
    piece *ptr = *start;
    while (ptr->next != NULL)
    {
        ptr->dados += 1;
        ptr = ptr->next;
    }

    return 1;
}
/*
    Funcao Option_1
        Cada caractere da lista recebe -1, em relacao ao seu valor ASCII
*/
int Option_1(List *start)
{
    piece *ptr = *start;
    while (ptr->next != NULL)
    {
        ptr->dados -= 1;
        ptr = ptr->next;
    }

    return 1;
}

/*
    Funcao Option2
        Cada caractere da lista recebe +3, em relacao ao seu valor ASCII
*/
int Option2(List *start)
{

    piece *ptr = *start;
    while (ptr->next != NULL)
    {
        ptr->dados += 3;
        ptr = ptr->next;
    }


    return 1;
}

/*
    Funcao Option_2
        Cada caractere da lista recebe -3, em relacao ao seu valor ASCII
*/
int Option_2(List *start)
{

    piece *ptr = *start;
    while (ptr->next != NULL)
    {
        ptr->dados -= 3;
        ptr = ptr->next;
    }


    return 1;
}

/*
    Funcao Option3
        Cada caractere da lista recebe +[1,2,3], em relacao ao seu valor ASCII
        O incremento dos valores occore em um formato ciclico.
*/
int Option3(List *start)
{
    int ammt = 1;

    piece *ptr = *start;
    while (ptr->next != NULL)
    {
        ptr->dados += ammt;
        ptr = ptr->next;

        if (ammt != 3)
            ammt++;
        else
            ammt = 1;
    }

    return 1;
}

/*
    Funcao Option_3
        Cada caractere da lista recebe -[1,2,3], em relacao ao seu valor ASCII
        O incremento dos valores occore em um formato ciclico.
*/
int Option_3(List *start)
{
    int ammt = 1;

    piece *ptr = *start;
    while (ptr->next != NULL)
    {
        ptr->dados -= ammt;
        ptr = ptr->next;

        if (ammt != 3)
            ammt++;
        else
            ammt = 1;
    }

    return 1;
}

/*
    Funcao Option4
        Cada caractere da lista recebe +[chave_numerica], em relacao ao seu valor ASCII
        O incremento dos valores occore em um formato ciclico.
*/
int Option4(List *start, int *key, int k_size)
{
    //quando count == k_size, comeca dnv
    int count = 0;

    piece *ptr = *start;

    while (ptr->next != NULL)
    {
        ptr->dados += key[count];
        ptr = ptr->next;

        if (count == (k_size - 1))
            count = 0;
        else
            count++;
    }

    return 1;
}

/*
    Funcao Option_4
        Cada caractere da lista recebe -[chave_numerica], em relacao ao seu valor ASCII
        O incremento dos valores occore em um formato ciclico.
*/
int Option_4(List *start, int *key, int k_size)
{
    //quando count == k_size, comeca dnv
    int count = 0;

    piece *ptr = *start;

    while (ptr->next != NULL)
    {
        ptr->dados -= key[count];
        ptr = ptr->next;

        if (count == (k_size - 1))
            count = 0;
        else
            count++;
    }

    return 1;
}

/*
    Funcao Option5
        A string eh criptografada segundo a funcao Option4
        Depois de criptografada a funcao insere um novo nodulo contendo '*' como caractere 
        Num intervalo de 3 a 3 nodulos.
*/
int Option5(List *start, int *key, int k_size)
{

    Option4(start, key, k_size);

    piece *ptr = *start;

    int count = 1;
    int pos = 0;
    int listsz = ListSize(start);

    while (ptr->next != NULL)
    {
        if (count == 3)
        {
            InsereAntesDe(start, (pos), '*');
            count = 0;
            listsz = ListSize(start);
        }
        else
            count++;

        pos++;

        // listsz eh utilizado para impedir de que um asterisco seja colocado na ultima posicao.
        if(pos == listsz-3)
            break;

        ptr = ptr->next;
    }

    return 1;
}

/*
    Funcao Option_5
        A funcao Option_5 primeiro remove todos os asteriscos
        Depois disso ela remove a encriptacao por meio da funcao Option_4
*/
int Option_5(List *start, int *key, int k_size)
{
    //remove the *
    int flag = 1;
    while (flag == 1)
    {
        flag = ApagaNode(start, '*');
    }

    //option_4;
    Option_4(start, key, k_size);

    return 1;
}