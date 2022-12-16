#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*----------------------------------------------------------------------------------------------------------------------------------------*/

typedef struct node 
{
    char dados;
    struct node *next;
}node;

typedef struct node* List;
typedef struct node piece;

/*----------------------------------------------------------------------------------------------------------------------------------------*/
// Arquivo lde.c

List *CriaLista();
void DeleteList(List *start);
int InsereFim(List *start, char data);
int InsereAntesDe(List *start, int pos, char data);
int ApagaPrimeira(List *start);
int ApagaNode(List *start, char val);
int ListSize(List *start);
int display(List *start);

/*----------------------------------------------------------------------------------------------------------------------------------------*/
// Arquivo option.c

int Option1(List *start);
int Option_1(List *start);
int Option2(List *start);
int Option_2(List *start);
int Option3(List *start);
int Option_3(List *start);
int Option4(List *start, int *key, int k_size);
int Option_4(List *start , int *key, int k_size);
int Option5(List *start, int *key, int k_size);
int Option_5(List *start, int *key, int k_size);