#ifndef __List__
#define __List__

/**
 * Autores: 
 * (11800970) Felipe de Alcantra Tome 
 * (11954374) Francisco Reis Nogueira 
*/

typedef struct _node {
    char *nomeEstacao;
    int codEstacao;
    int codProxEstacao;
    long posRegistro;
    struct _node *next;
}Node;

typedef Node* List;
typedef Node node;

List *createList();
void deleteList(List *root);
int insertEnd(List *root, int *nroEstacoes, int *nroPares, char *stationName, int stationNumber, int nextStationNumber, long posRegister);
int removeNode(List *root, int *nroEstacoes, int *nroPares, char *stationName, int stationNumber, int nextStationNumber, long posRegister);
int listSize(List *root);
void displayList(List *root);

int checkForStationInList(List *root, char *stationToBeChecked);


#endif
