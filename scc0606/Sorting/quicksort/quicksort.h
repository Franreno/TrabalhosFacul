#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define TAM 10000
#define repeticoes 1

typedef int elem;

typedef struct list
{
    elem *elements;
    elem *copy;
    long listSize;
}list;

void create(list *l);
void destroy(list *l);
int insert(list *l, elem e);
void printList(list *l);

void sortQuickSort(list *l);
void insertUniqueElements(list *l);