#include "lde.h"


/*
    Funcao CriaLista
        cria o ponteiro duplo pra lista, o 'header'
*/
List *CriaLista()
{

    List *start = (List *)malloc(sizeof(List));

    // se nao estiver setado como nulo, porque acabou de ser criado ele eh colocado como nulo.
    if (start != NULL)
    {
        *start = NULL;
    }

    return start;
}


/*
    Funcao DeleteList
        Apaga a lista inteira.
*/
void DeleteList(List *start)
{
    // o start tem que estar diferente de nulo pra ter algo pra apagar
    if (start != NULL)
    {
        //ponteiro auxiliar que percorrera a lista toda a fim de apagar cada node
        piece *ptr;

        // enquanto o ponteiro start nao chegar num ponto nulo, ou seja, enquanto a lista nao acabar
        while ((*start) != NULL)
        {
            // o ponteiro auxiliar recebe o endereco de start
            ptr = *start;
            *start = (*start)->next; // start vai pro proximo lugar da lista
            free(ptr);               // o endereco que o ponteiro auxiliar estava apontando eh liberado
        }
        free(start); // e por fim o start eh liberado;
    }
}

/*
    Funcao InsereFim
        Insere um novo nodulo no final da lista.
*/
int InsereFim(List *start, char data)
{

    if (start == NULL)
        return 0;

    piece *new_node;
    new_node = (piece *)malloc(sizeof(piece));
    new_node->dados = data;
    new_node->next = NULL;

    // se a lista ainda esta vazia nao o fim sera igual ao comeco entao tanto faz
    if ((*start) == NULL)
        *start = new_node;
    else
    {
        // se a lista nao esta vazia, o ponteiro auxiliar percorre pela lista ate encontrar a ultima posicao;
        piece *ptr;

        ptr = *start;

        while (ptr->next != NULL)
            ptr = ptr->next;

        /* 
            quando encontrou a ultima posicao o campo proximo do ponteiro auxiliar
            deixa de apontar para nulo e aponta para o novo nodulo
            e o campo proximo do novo nodulo ja esta apontando pra nulo; 
        */

        ptr->next = new_node;

        return 1;
    }

    return 0;
}


/*
    Funcao InsereAntesDe:
        insere um novo nodulo antes de certa posicao
        Recebe: 
            start: o comeco da lista.
            pos:   depois de x nodulos o um novo nodulo sera incluido.
            data:  o dado que sera colocado na lista.
*/
int InsereAntesDe(List *start, int pos, char data)
{
    if (start == NULL)
        return 0;

    piece *new_node, *ptr, *preptr;
    int i = 0;

    new_node = (piece *)malloc(sizeof(piece));
    new_node->dados = data;
    ptr = (*start);

    // a lista eh percorrida enquanto nao acaba e o contador seja menor da posicao a ser colocada
    while (ptr->next != NULL && i <= pos)
    {
        preptr = ptr;
        ptr = ptr->next;
        i++;
    }

    if (ptr == NULL)
    {
        return 0;
    }
    else
    {
        preptr->next = new_node;
        new_node->next = ptr;
        return 1;
    }
}


/*
    Funcao ApagaPrimeira
        Apaga o primeiro nodulo da lista.
*/
int ApagaPrimeira(List *start)
{
    if (start == NULL)
        return 0;
    if ((*start) == NULL)
        return 0;

    piece *ptr;
    ptr = *start;
    (*start) = (*start)->next;
    free(ptr);

    return 1;
}


/*
    Funcao ApagaNode:
        Remove o nodulo com um certo valor dentro, conforme o valor passado.
*/
int ApagaNode(List *start, char val)
{
    if (start == NULL)
        return 0;
    if ((*start) == NULL)
    {
        return 0;
    }

    piece *ptr, *preptr;
    ptr = (*start);

    if (ptr->dados == val) //se for o dado estiver no comeco da lista, ele eh removido usando a funcao ApagaPrimeira.
    {
        ApagaPrimeira(start);
        return 1;
    }
    else
    {
        // Se o valor nao estiver na primeira posicao, a lista eh percorrida ate encontrar o valor.
        while (ptr->dados != val && ptr->next != NULL)
        {
            preptr = ptr;
            ptr = ptr->next;
        }

        // Se o valor nao for encontrado na lista a funcao retorna 0
        if (ptr->next == NULL)
            return 0;

        preptr->next = ptr->next;

        free(ptr);
        return 1;
    }

    return 0;
}


/*
    Funcao ListSize:
        Retorna o valor do tamanho da lista, a quantidade de nodulos presentes.
*/
int ListSize(List *start)
{
    if (start == NULL)
        return 0;
    int count = 0;
    piece *ptr = *start;
    while (ptr != NULL)
    {
        count++;
        ptr = ptr->next;
    }

    return count;
}


/* 
    Funcao display:
        Mostra o conteudo da lista em cada nodulo
*/
int display(List *start)
{
    if (start == NULL)
        return 0;

    piece *ptr = *start;
    
    while (ptr != NULL)
    {        
        printf("%c", ptr->dados);
        ptr = ptr->next;
    }

    return 1;
}
