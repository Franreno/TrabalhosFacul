
/**
 * Autores: 
 * (11800970) Felipe de Alcantra Tome 
 * (11954374) Francisco Reis Nogueira 
*/

#include "binary.h"

// Read functions

/**
 * Le o conteudo presente no cabecalho de um arquivo binario.
 * @param c Ponteiro para o cabecalho.
 * @param bin Ponteiro para o arquivo binario. 
*/
void readCabecalho(CABECALHO *c, FILE *bin)
{
    fread(&(c->status), sizeof(char), 1, bin);
    fread(&(c->topoLista), sizeof(long), 1, bin);
    fread(&(c->nroEstacoes), sizeof(int), 1, bin);
    fread(&(c->nroParesEstacao), sizeof(int), 1, bin);
}

/**
 * Le os tres primeiros campos de um registro a partir de um arquivo binario.
 * @param r Ponteiro para o registro.
 * @param bin Ponteiro para o arquivo binario.
*/
void readFirstThreeFields(REGISTRO *r, FILE *bin)
{
    fread(&(r->removido), sizeof(char), 1, bin);
    fread(&(r->tamanhoRegistro), sizeof(int), 1, bin);
    fread(&(r->proxLista), sizeof(long), 1, bin);
}

/**
 * Le os campos de tamanho fixo de um registro em um arquivo binario.
 * @param r Ponteiro para o registro.
 * @param bin Ponteiro para o arquivo binario.
*/
void readIntegerFieldsAtRegister(REGISTRO *r, FILE *bin)
{
    fread(&(r->codEstacao), sizeof(int), 1, bin);
    fread(&(r->codLinha), sizeof(int), 1, bin);
    fread(&(r->codProxEstacao), sizeof(int), 1, bin);
    fread(&(r->distProxEstacao), sizeof(int), 1, bin);
    fread(&(r->codLinhaIntegra), sizeof(int), 1, bin);
    fread(&(r->codEstIntegra), sizeof(int), 1, bin);
}

/**
 * Le uma string de tamanho dinamico em um arquivo binario.
 * @param dest Ponteiro de referencia a string que sera criada.
 * @param bin Ponteiro para o arquivo binario.
*/
void readSingleStringFieldAtRegister(char **dest, FILE *bin)
{
    char *tempLine = (char *)malloc(sizeof(char) * 64);
    memset(tempLine, 0, 64);

    // Ler o nomeEstacao -> Tamanho desconhecido -> Ler ate encontrar um '|'
    int nomeEstacaoSize = parseSingleStringFromBinaryFile(bin, &tempLine);
    // Aloca o tamanho no registro
    (*dest) = (char *)malloc(sizeof(char) * (nomeEstacaoSize));
    strcpy((*dest), tempLine);

    free(tempLine);
}

/**
 * Le os campos de tamanho variavel de um registro em um arquivo binario.
 * @param r Ponteiro para o registro.
 * @param bin Ponteiro para o arquivo binario.
*/
void readStringFieldsAtRegister(REGISTRO *r, FILE *bin)
{
    readSingleStringFieldAtRegister(&r->nomeEstacao, bin);

    readSingleStringFieldAtRegister(&r->nomeLinha, bin);
}

/**
 * Leitura de um unico registro dentro de um arquivo binario.
 * @param r Ponteiro para um registro.
 * @param bin Ponteiro para o arquivo binario.
 * @return 0 se o arquivo esta logicamente removido. 1 caso o contrario.
*/
int readSingleRegister(REGISTRO *r, FILE *bin)
{
    long whereIWas = ftell(bin);
    readFirstThreeFields(r, bin);
    if (r->removido == REMOVIDO)
    {
        // Se removeu volta uma posicao pra pular pro proximo registro.
        fseek(bin, -(sizeof(long)), SEEK_CUR);
        return 0;
    }

    readIntegerFieldsAtRegister(r, bin);

    readStringFieldsAtRegister(r, bin);
    long whereIam = ftell(bin);

    // Vai pro prox registro pulando os lixos.
    int garbageOffset = whereIam - whereIWas;
    int registerSize = r->tamanhoRegistro + sizeof(char) + sizeof(int);

    // Se for menor eh pq faltou campos para ler, ou seja, teve lixos que nao foram lidos.
    if (garbageOffset < registerSize)
    {
        // Quantidade de lixos presente no registro
        int whereINeedToGo = registerSize - garbageOffset;
        // Pular os lixos presentes no registro
        fseek(bin, whereINeedToGo, SEEK_CUR);
    }

    return 1;
}

void procuraEstacao(int codigoDeProcura, REGISTRO *r, FILE *bin)
{
    long startPosition = ftell(bin);
    // Vai pro comeco
    fseek(bin, 0, SEEK_SET);

    long fileSize = getFileSize(bin);

    REGISTRO aux;
    while (ftell(bin) != fileSize)
    {
        if (!readSingleRegister(&aux, bin))
        {
            fseek(bin, aux.tamanhoRegistro, SEEK_CUR);
            continue;
        }

        if (aux.codEstacao == codigoDeProcura)
        {
            copyRegisterContents(r, &aux);
            break;
        }
    }

    // Volta para onde estava
    fseek(bin, startPosition, SEEK_SET);
}