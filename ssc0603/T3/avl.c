#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "T3.h"

struct NO{
    int acessos;
    char en_word[32];
    char pt_word[32];
    int altura;
    struct NO *esq;
    struct NO *dir;
};

ArvAVL* cria_ArvAVL() {
    ArvAVL* raiz = (ArvAVL*) malloc(sizeof(ArvAVL));
    if(raiz != NULL)
        *raiz = NULL;
    return raiz;
}

void libera_NO(struct NO* no){
    if(no == NULL)
        return;
    libera_NO(no->esq);
    libera_NO(no->dir);
    free(no);
    no = NULL;
}

void libera_ArvAVL(ArvAVL* raiz){
    if(raiz == NULL)
        return;
    libera_NO(*raiz);//libera cada n�
    free(raiz);//libera a raiz
}

int altura_NO(struct NO* no){
    if(no == NULL)
        return -1;
    else
    return no->altura;
}

int fatorBalanceamento_NO(struct NO* no){
    return labs(altura_NO(no->esq) - altura_NO(no->dir));
}

int maior(int x, int y){
    if(x > y)
        return x;
    else
        return y;
}

int estaVazia_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

int totalNO_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = totalNO_ArvAVL(&((*raiz)->esq));
    int alt_dir = totalNO_ArvAVL(&((*raiz)->dir));
    return(alt_esq + alt_dir + 1);
}

int altura_ArvAVL(ArvAVL *raiz){
    if (raiz == NULL)
        return 0;
    if (*raiz == NULL)
        return 0;
    int alt_esq = altura_ArvAVL(&((*raiz)->esq));
    int alt_dir = altura_ArvAVL(&((*raiz)->dir));
    if (alt_esq > alt_dir)
        return (alt_esq + 1);
    else
        return(alt_dir + 1);
}


void emOrdem_ArvAVL(ArvAVL *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        emOrdem_ArvAVL(&((*raiz)->esq));
        printf("%s %d\n",(*raiz)->en_word , (*raiz)->acessos);
        emOrdem_ArvAVL(&((*raiz)->dir));
    }
}

void RotacaoLL(ArvAVL *A){//LL
    struct NO *B;
    B = (*A)->esq;
    (*A)->esq = B->dir;
    B->dir = *A;
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->esq),(*A)->altura) + 1;
    *A = B;
}

void RotacaoRR(ArvAVL *A){//RR
    struct NO *B;
    B = (*A)->dir;
    (*A)->dir = B->esq;
    B->esq = (*A);
    (*A)->altura = maior(altura_NO((*A)->esq),altura_NO((*A)->dir)) + 1;
    B->altura = maior(altura_NO(B->dir),(*A)->altura) + 1;
    (*A) = B;
}

void RotacaoLR(ArvAVL *A){//LR
    RotacaoRR(&(*A)->esq);
    RotacaoLL(A);
}

void RotacaoRL(ArvAVL *A){//RL
    RotacaoLL(&(*A)->dir);
    RotacaoRR(A);
}


//Insercao de modo AVL
int insere_ArvAVL(ArvAVL *raiz, int acessos, char en_word[32] , char pt_word[32] )
{
    int res;
    if(*raiz == NULL){

        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL)
            return 0;

        strcpy(novo->en_word, en_word);
        strcpy(novo->pt_word, pt_word);
        novo->acessos = acessos;
        novo->esq = NULL;
        novo->dir = NULL;
        *raiz = novo;
        return 1;
    }

    struct NO *atual = *raiz;


    // a nova palavra esta em prioridade alfabetica.
    if(strcmp(en_word , atual->en_word) < 0)
    {
        if( (res = insere_ArvAVL(&(atual->esq) , acessos , en_word, pt_word ) ) == 1)
        {
            if(fatorBalanceamento_NO(atual) >= 2)
            {
                if(strcmp( en_word, (*raiz)->esq->en_word ) < 0 )
                {
                    RotacaoLL(raiz);
                }
                else
                {
                    RotacaoLR(raiz);
                }
            }
        }
    }
    else
    {
        if(strcmp(en_word , atual->en_word ) > 0)
        {
            if( (res = insere_ArvAVL(&(atual->dir) , acessos , en_word , pt_word )) == 1) 
            {
                if(fatorBalanceamento_NO(atual) >= 2)
                {
                    if(strcmp((*raiz)->dir->en_word , en_word ) < 0)
                    {
                        RotacaoRR(raiz);
                    }
                    else
                    {
                        RotacaoRL(raiz);
                    }
                }
            }
        }
        else
        {
            return 0;
        }
    }

    atual->altura = maior(altura_NO(atual->esq),altura_NO(atual->dir)) + 1;

    return res;
}



/*
------------------------------------------------------------------------------------------------
*/

//procura a palavra pela arvore.
int searchTree(ArvAVL *raiz , char word_to_translate[32])
{
    if (raiz == NULL || (*raiz) == NULL )
        return 0;

    struct NO *this = *raiz;

    //roda a arvore ate que chegue a um campo nulo ou encontre a para traduzir.
    while( this != NULL )
    {
        //se a palavra pra traducao for encontrada na arvore...
        if ( strcmp( this->en_word,  word_to_translate) == 0 )
        {
            // ... eh feito o output da palavra traduzida
            printf("%s\n" , this->pt_word);
            this->acessos++;
            return 1;
        }

        //percorre a arvore de maneira alfabetica
        if ( strcmp(word_to_translate , this->en_word) > 0)
            this = this->dir;
        else
            this = this->esq;  
    }

    return 0;
}


//funcao que compara as strings de acordo com o tamanho requesitado
int compareUntilSize(char *s1, char *s2, int size)
{
    // se o tamanho do requesitado para a comparacao for maior que a string
    // que esta sendo comparada dentro da arvore ele cancela.
    if( size > strlen(s2) )
        return -1;
    
    // se tiver alguma letra diferente na comparacao das strings ele cancela.
    for(int i=0; i<size; i++)
    {
        if( s1[i] != s2[i] )
            return -1;
    }

    return 0;
}

//funcao de autocompletar
int autocomplete(ArvAVL *raiz, int access ,char word_to_complete[32])
{
    // Need to serach the tree for words that has word_to_complete
    // and also has at least the acess number that was given.
    if(raiz == NULL || (*raiz) == NULL)
        return 0;

    struct NO *this = (*raiz);

    //percorre a arvore ate chegar a um nodo nulo
    while(this != NULL)
    {
        //comparar as strings como a funcao acima.
        if ( compareUntilSize(word_to_complete , this->en_word , strlen(word_to_complete) ) == 0)
        {
            // verificacao recursiva dos nodulos da arvore.
            if( this->esq != NULL)
                autocomplete( &((this)->esq) , access , word_to_complete);


            // se a palavra que contem as letras que eu quero autocompletar tiver o numero de acessos
            // igual ou maior aos que foi requesitado ele imprime a palavra.
            if(this->acessos >= access)
                printf("%s\n" , this->en_word);
            

            if( this->dir != NULL)
                autocomplete( &((this)->dir) , access , word_to_complete);
            

            return 1;
        }

        // verificacao recursivav dos nodulos da arvore.
        if ( strcmp(word_to_complete , this->en_word) > 0 )
            this = this->dir;
        else
            this = this->esq;
    }

    return 0;
}