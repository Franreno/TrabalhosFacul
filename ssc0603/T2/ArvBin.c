#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArvBin.h"

//Forma da struct de uma arvore binaria
struct node
{
    char info[1024];
    struct node *esq;
    struct node *dir;
};

//Cria a raiz da arvore binaria
ArvBin* criaArvBin()
{
    ArvBin* raiz = (ArvBin*)malloc(sizeof(ArvBin));
    if (raiz != NULL)
    {
        *raiz = NULL;
    }

    return raiz;
}

// Funcao de recursao da liberacao da arvore binaria
void liberaNode(struct node* no)
{
    if(no == NULL)
        return;
    liberaNode(no->esq);
    liberaNode(no->dir);
    free(no);

    no = NULL;
}

//Funcao de liberar a arvore binaria
void liberaArvBin(ArvBin* raiz)
{
    if (raiz == NULL)
        return;
    
    liberaNode(*raiz);
    free(raiz);

}


//Funcao para inserir na arvore binaria.
//Recebe:
//		raiz, a string pra ser colocada no nodulo, 
//		o tipo de insercao (esquerda, direita) e 
// 		stdado serve para guardar o nodulo pai da insercao da vez.

int insertBinaryTree(ArvBin* root, char dado[], int flag, char stdado[])
{
    if(root == NULL)
        return 0;
    
	//criacao do novo nodulo
    struct node* new_node = (struct node*)malloc(sizeof(struct node));
    
    strcpy(new_node->info , dado);
    new_node->esq = NULL;
    new_node->dir = NULL;

    if( (*root) == NULL)
    {   
		// se nao tiver nada na *raiz, o primeiro nodulo eh colocado aqui
        (*root) = new_node;
        return 1;
    }
    else
    {
		// funcao pra procurar onde ta o nodulo stdado, e assim ser inserido 'nele',
		// na esquerda ou na direita
		SearchNode(root, new_node, flag, stdado);    
    }

    return 1;
}


// Funcao recursiva que procura o nodulo em questao
// Recebe os mesmos parametros que a funcao 'insertBinaryTree'
// OBS: eh essa funcao que insere de fato o novo nodulo na arvore
int SearchNode(ArvBin* raiz, struct node* valor, int flag, char stdado[])
{   
	// se a *raiz tiver vazia ele nao poderia estar aqui
    if(raiz == NULL || (*raiz) == NULL)
        return 0;

	//ponteiro auxiliar
    struct node* atual = (*raiz);

	// se o dado do nodo atual for igual ao nodulo pai que deve ser inserido.
    if ( strcmp( atual->info , stdado ) == 0 )
    {
        if (flag == 0)
        {
			//eh o nodulo pai
            atual = valor;
        }
        else if( flag == 1)
        {
			//eh o filho esquerdo
            atual->esq = valor;
        }
        else if( flag == 2)
        {
			// eh o filho direito
            atual->dir = valor;
        }
        
        return 1;
    } 

	// Recusao para encontrar o nodulo correto da insercao.
    SearchNode( &((*raiz)->esq) , valor , flag , stdado);
    SearchNode( &((*raiz)->dir) , valor , flag, stdado);
    

    return 1;
}

// Funcao pra mostrar o conteudo da arvore binaria
// na forma que o trabalho pede.
// Recebe a raiz da arvore.
int mostraArvBin(ArvBin *raiz)
{
	//Valores de nodos de saida e nodos totais, respectivamente.
    int saida = 0;
    int total = 0;
    if (raiz == NULL || *raiz == NULL)
        return 0;

	//ponteiro auxiliar
    struct node* atual = (*raiz);
	
	//chama a recursao de visitar os nodulos da arvore
    visitaArvBin(atual , &total , &saida);

	//print dos valores de nodulo total e nodulo de saida
    printf("%d %d\n" , total , saida);
    return 1;
}


// Funcao recursiva de passar em todos os nodulos da arvore e dar print na forma do trabalho
// Recebe:
// 		o nodulo atual, o totais de nodulos, e nodulos de saida, que ela ja passou.
int visitaArvBin(struct node* atual, int *total, int *saida)
{
	//numero de filhos de um nodulo
    int nfilhos;
	
	//string pra impressao do formato "ED" || "E" || "D" || "F"
    char str[4];
    
	//Cadad vez que essa funcao eh chamada eh porque tem mais um nodulo, assim:
	(*total)++;

    //Imprimir o nome do nodulo, quantos filhos ele tem, e se eh pra esq dir ou folha
    if(atual != NULL)
    {
		//se tiver dois filhos
        if(atual->esq != NULL && atual->dir != NULL)
        {
            nfilhos = 2;
            strcpy(str , "ED\0");
        }
		//se tiver um filho esquerdo
        else if(atual->esq != NULL)
        {
            nfilhos = 1;
            strcpy(str, "E\0");
        }
		//se tiver um filho direito
        else if(atual->dir != NULL)
        {
            nfilhos = 1;
            strcpy(str, "D\0");
        }
		//se nao tiver nenhum filho
        else
        {
            nfilhos = 0;
            strcpy(str, "F\0");
            (*saida)++;
        }

		//impressao do tipo de nodulo que foi encontrado pela funcao
        printf("%s %d %s\n" , atual->info , nfilhos , str);
    }

	//parte recursiva da funcao.
    if(atual->esq != NULL)
        visitaArvBin(atual->esq, total, saida);
    if(atual->dir != NULL)
        visitaArvBin(atual->dir, total, saida);

   return 1; 
}