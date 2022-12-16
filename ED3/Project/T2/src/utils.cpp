/**
 * Autores: 
 * (11800970) Felipe de Alcantra Tome 
 * (11954374) Francisco Reis Nogueira 
*/

#include "utils.h"

/**
 * Pega o valor do tamanho de um arquivo qualquer.
 * @param arq Ponteiro para um arquivo aberto qualquer.
*/
long getFileSize(FILE *arq)
{
    fseek(arq, 0, SEEK_END);
    long fileSize = ftell(arq);
    fseek(arq, 0, SEEK_SET);

    return fileSize;
}

/*--------------------------------------------*/

/**
 * Le os valores a partir de um arquivo binario de uma string de tamanho 
 * variavel e atribui esses valores a uma string. A leitura eh feita ate encontrar 
 * um delimitador '|'.
 * @param bin Ponteiro para o arquivo binario.
 * @param line Ponteiro de referencia para a String que tera os valores lidos.
*/
int parseSingleStringFromBinaryFile(FILE *bin, char **line)
{
    char *stringPointer = (char *)malloc(sizeof(char));
    *stringPointer = '0';
    int charCounter = 0;

    while (*stringPointer != DELIMITADOR)
    {
        fread(stringPointer, sizeof(char), 1, bin);
        if (*stringPointer == DELIMITADOR)
            break;
        (*line)[charCounter] = *stringPointer;
        charCounter++;
    }
    charCounter++;
    (*line)[charCounter] = '\0';

    free(stringPointer);
    return charCounter;
}

/*--------------------------------------------*/

/**
 * Verifica se uma string de input eh nula
 * @param str String que contem o valor que sera verificado.
*/
int isNull(char *str)
{
    int flag = 0;
    if (str[0] == 'N')
        flag = 1;
    return flag;
}

/**
 * Imprime os valores de um registro
 * @param r Ponteiro para um registro
*/
void printRegistro(REGISTRO *r)
{
    if (r == NULL)
        return;
    r->codEstacao == -1 ? printf("NULO ") : printf("%d ", r->codEstacao);
    (!*r->nomeEstacao) ? printf("NULO ") : printf("%s ", r->nomeEstacao);
    r->codLinha == -1 ? printf("NULO ") : printf("%d ", r->codLinha);
    (!*r->nomeLinha) ? printf("NULO ") : printf("%s ", r->nomeLinha);
    r->codProxEstacao == -1 ? printf("NULO ") : printf("%d ", r->codProxEstacao);
    r->distProxEstacao == -1 ? printf("NULO ") : printf("%d ", r->distProxEstacao);
    r->codLinhaIntegra == -1 ? printf("NULO ") : printf("%d ", r->codLinhaIntegra);
    r->codEstIntegra == -1 ? printf("NULO \n") : printf("%d \n", r->codEstIntegra);
}

/*----------------------------------------------------------------*/

/**
 * Imprime na tela todos os registros que nao estao logicamnete removidos de um arquivo binario.
 * @param bin Ponteiro para o arquivo binario que sera lido.
 * @return 1 para sucesso, 0 para erro.
*/
int outputBinary(FILE *bin)
{
    // Pegar tamanho do arquivo
    long fileSize = getFileSize(bin);

    //Ler o cabecalho. Primeiros 4 campos.
    CABECALHO c;
    readCabecalho(&c, bin);

    REGISTRO r;
    char *tempLine = (char *)malloc(sizeof(char) * 64);
    memset(tempLine, 0, 64);

    int registersRead = 0;
    while (ftell(bin) != fileSize)
    {
        if (!readSingleRegister(&r, bin))
        {
            fseek(bin, r.tamanhoRegistro, SEEK_CUR);
            continue;
        }
        else
            registersRead++;

        printRegistro(&r);

        //Limpar strings
        free(r.nomeEstacao);
        free(r.nomeLinha);
        memset(tempLine, 0, 64);
    }

    free(tempLine);

    if (!registersRead)
        return 0;

    return 1;
}

void copyRegisterContents(REGISTRO *dest, REGISTRO *src)
{
    dest->removido = src->removido;
    dest->tamanhoRegistro = src->tamanhoRegistro;
    dest->proxLista = src->proxLista;
    dest->codEstacao = src->codEstacao;
    dest->codLinha = src->codLinha;
    dest->codProxEstacao = src->codProxEstacao;
    dest->distProxEstacao = src->distProxEstacao;
    dest->codLinhaIntegra = src->codLinhaIntegra;
    dest->codEstIntegra = src->codEstIntegra;

    dest->nomeEstacao = (char *)malloc(sizeof(char) * strlen(src->nomeEstacao));
    dest->nomeLinha = (char *)malloc(sizeof(char) * strlen(src->nomeLinha));

    strcpy(dest->nomeEstacao, src->nomeEstacao);
    strcpy(dest->nomeLinha, src->nomeLinha);
}
