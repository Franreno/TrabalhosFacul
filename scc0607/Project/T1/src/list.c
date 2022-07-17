/**
 * Autores: 
 * (11800970) Felipe de Alcantra Tome 
 * (11954374) Francisco Reis Nogueira 
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "list.h"

/**
 * Criacao da Lista.
*/
List *createList()
{
    List *root = (List *)malloc(sizeof(List));
    if (root != NULL)
        *root = NULL;
    return root;
}

/**
 * Destruicao da lista. Liberacao de memoria.
*/
void deleteList(List *root)
{
    if (root == NULL)
        return;

    node *ptr;
    while ((*root) != NULL)
    {
        ptr = (*root);
        (*root) = (*root)->next;
        free(ptr->nomeEstacao);
        free(ptr);
    }
    free(root);
}

/**
 * Insere um novo no da lista no fim dela. Aproveita o caminho de insercao na Lista e calcula os valores do 
 * nroEstacoes e nroParesEstacoes. Tambem armazena o byte offset do registro, utilizado na remocao de registros.
 * @param root Ponteiro para o nó principal da lista.
 * @param nroEstacoes Ponteiro de referencia para a quantidade de estacoes.
 * @param nroPares Ponteiro de referencia para a quantidade de pares.
 * @param stationName Nome da estacao que sera inserida na lista.
 * @param stationNumber Codigo da estacao que sera inserida na lista.
 * @param nexStationNumber Codigo da proxima estacao que sera inserida na lista.
 * @param posRegister Byte offset do registro que esta sendo inserido.
*/
int insertEnd(List *root, int *nroEstacoes, int *nroPares, char *stationName, int stationNumber, int nextStationNumber, long posRegister)
{
    if (root == NULL)
        return 0;

    node *newNode = (node *)malloc(sizeof(node));
    if (newNode == NULL)
        return 0;

    // Adiciona os valores na lista
    newNode->codEstacao = stationNumber;
    newNode->codProxEstacao = nextStationNumber;
    newNode->posRegistro = posRegister;

    //Alocate string size.
    int stationNameSize = strlen(stationName) + 1;
    newNode->nomeEstacao = (char *)malloc(sizeof(char) * stationNameSize);
    strcpy(newNode->nomeEstacao, stationName);

    // Insere no fim entao o prox eh nulo.
    newNode->next = NULL;

    int alreadyHasStation = 0;
    int alreadyHasPair = 0;

    // Se a lista esta vazia ele insere no comeco
    if ((*root) == NULL)
    {
        (*root) = newNode;
        (*nroEstacoes)++;
        (*nroPares)++;
    }
    else
    {
        node *ptr = (*root);
        while (ptr->next != NULL)
        {
            // Verificar se a estacao que esta sendo adiconada esta na lista.
            if (!strcmp(ptr->nomeEstacao, stationName))
                alreadyHasStation = 1;

            // Verificar se o par ja existe.
            if ((ptr->codEstacao == stationNumber) && (ptr->codProxEstacao == nextStationNumber))
                alreadyHasPair = 1;

            ptr = ptr->next;
        }

        if (!alreadyHasStation && stationName[0] != '\0')
            (*nroEstacoes)++;

        if (!alreadyHasPair && newNode->codProxEstacao != -1 && newNode->codEstacao != -1)
            (*nroPares)++;

        // Atribui ao proximo no, que seria nulo, o novo no.
        ptr->next = newNode;
    }

    return 1;
}
