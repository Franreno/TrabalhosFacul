
/**
 * Autores: 
 * (11800970) Felipe de Alcantra Tome 
 * (11954374) Francisco Reis Nogueira 
*/

#include "binary.h"

/**
 * Escreve os quatro campos do cabecalho em um arquivo binario.
 * @param bin Ponteiro para o arquivo binario.
 * @param c Ponteiro para o cabecalho.
*/
void writeCabecalho(FILE *bin, CABECALHO *c)
{
    fwrite(&c->status, sizeof(char), 1, bin);
    fwrite(&c->topoLista, sizeof(long), 1, bin);
    fwrite(&c->nroEstacoes, sizeof(int), 1, bin);
    fwrite(&c->nroParesEstacao, sizeof(int), 1, bin);
}

/**
 * Escreve os valores de tamanho fixo de um registro em um arquivo binario.
 * @param bin Ponteiro para o arquivo binario.
 * @param r Ponteiro para o registro.
*/
void writeIntegerAtBinary(FILE *bin, REGISTRO *r)
{
    fwrite(&r->removido, sizeof(char), 1, bin);

    fwrite(&r->tamanhoRegistro, sizeof(int), 1, bin);

    fwrite(&r->proxLista, sizeof(long), 1, bin);

    fwrite(&r->codEstacao, sizeof(int), 1, bin);

    fwrite(&r->codLinha, sizeof(int), 1, bin);

    fwrite(&r->codProxEstacao, sizeof(int), 1, bin);

    fwrite(&r->distProxEstacao, sizeof(int), 1, bin);

    fwrite(&r->codLinhaIntegra, sizeof(int), 1, bin);

    fwrite(&r->codEstIntegra, sizeof(int), 1, bin);
}

/**
 * Escreve a string nome estacao no binario e coloca o delimitador no final dela.
 * @param bin Ponteiro para o arquivo binario.
 * @param r Ponteiro para o registro.
*/
int writeStringNomeEstacao(FILE *bin, REGISTRO *r)
{
    int nomeEstacaoSize = strlen(r->nomeEstacao);

    char deli = DELIMITADOR;
    fwrite(r->nomeEstacao, sizeof(char), nomeEstacaoSize, bin);
    fwrite(&deli, sizeof(char), 1, bin);

    return nomeEstacaoSize;
}

/**
 * Escreve a string nome linha no binario e coloca o delimitador no final dela.
 * @param bin Ponteiro para o arquivo binario.
 * @param r Ponteiro para o registro.
*/
int writeStringNomeLinha(FILE *bin, REGISTRO *r)
{
    int nomeLinhaSize = strlen(r->nomeLinha);

    char deli = DELIMITADOR;
    fwrite(r->nomeLinha, sizeof(char), nomeLinhaSize, bin);
    fwrite(&deli, sizeof(char), 1, bin);

    return nomeLinhaSize;
}

/**
 * Escreve as duas strings de tamanhos dinamicos no arquivo binario.
 * @param bin Ponteiro para o arquivo binario.
 * @param r Ponteiro para o registro.
*/
void writeStringAtBinary(FILE *bin, REGISTRO *r)
{
    writeStringNomeEstacao(bin, r);
    writeStringNomeLinha(bin, r);
}

/**
 * Escreve o caractere lixo '$' n vezes no arquivo binario.
 * @param bin Ponteiro para o arquivo binario.
 * @param n Quantidade de caracteres lixos a serem escritos.
*/
void writeTrash(FILE *bin, int n)
{
    for (int i = 0; i < n; i++)
        fwrite(trashChar, sizeof(char), 1, bin);
}

/**
 * Escreve em um arquivo binario os campos de um registro.
 * @param bin Ponteiro para o arquivo binario.
 * @param r Ponteiro para a struct registro.
 * @return 1 para sucesso, 0 para erro.
*/
int writeBin(FILE *bin, REGISTRO *r)
{
    if (r == NULL)
        return 0;

    writeIntegerAtBinary(bin, r);
    writeStringAtBinary(bin, r);

    return 1;
}

/**
 * Funcao que rescreve o cabecalho inteiro. Percorre todo o arquivo e calcula o 
 * nroEstacoes e nroPares de estacoes. Eh utilizado quando ocorre varias alteracoes no arquivo
 * binario no meio do processamento.
 * @param c Ponteiro para o cabecalho.
 * @param bin Ponteiro para o arquivo binario.
*/
void rewriteCabecalho(CABECALHO *c, FILE *bin)
{
    long fileSize = getFileSize(bin);

    long guardaTopoLista = c->topoLista;
    readCabecalho(c, bin);
    c->status = INCONSISTENTE;
    c->nroEstacoes = 0;
    c->nroParesEstacao = 0;
    c->topoLista = guardaTopoLista;
    List *root = createList();

    REGISTRO r;
    while (ftell(bin) != fileSize)
    {
        // Se for 0 registro esta logicamente removido
        if (!readSingleRegister(&r, bin))
        {
            fseek(bin, r.tamanhoRegistro, SEEK_CUR);
            continue;
        }
        else
        {
            insertEnd(root, &c->nroEstacoes, &c->nroParesEstacao, r.nomeEstacao, r.codEstacao, r.codProxEstacao, 0);
            free(r.nomeEstacao);
            free(r.nomeLinha);
        }
    }

    c->status = CONSISTENTE;
    rewind(bin);
    writeCabecalho(bin, c);
    deleteList(root);
}

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

/**
 * Leitura de um registro removido no arquivo binario.
 * Verifica se ele possui um tamanho acessivel ao registro que sera inserido.
 * @param aux Registro auxiliar de leitura.
 * @param bin Ponteiro para o arquivo binario.
 * @param optimalSize Tamanho do registro que sera inserido.
 * @return 0 se esse o tamanho do registro a ser inserido eh menor do tamanho do registro lido.
 * -1 se chegou no final da lista dos removidos.
 * 1 se encontrou um registro bom para a insercao.
*/
int readFromRemovedRegister(REGISTRO *aux, FILE *bin, int *optimalSize)
{
    // Ler os campos removido e tamanho registro.
    readFirstThreeFields(aux, bin);

    //Verificar se o tamanho desse registro eh maior que o optimalSize.
    if (*optimalSize <= aux->tamanhoRegistro)
    {
        //Pode inserir nesse daqui.
        readIntegerFieldsAtRegister(aux, bin);
        readStringFieldsAtRegister(aux, bin);
        fseek(bin, -(sizeof(char) + sizeof(int) + aux->tamanhoRegistro), SEEK_CUR);

        return 1;
    }
    //Tem que ir prox final do binario.
    else if (aux->proxLista == -1)
        return -1;
    //Tem que ir pra prox posicao do proxLista.
    else
        return 0;
}

/**
 * Faz a busca no arquivo binario com o conteudo de busca e escreve as atualizacoes nos lugares corretos.
 * Procurar registro que batem com a pesquisa -> Cabe no registro ? inserir as atualizacoes nele. : Remover 
 * o registro lido e inserir a atualizacao com reaproveitamento de registros logicamente removidos.
 * @param bin Ponteiro para o arquivo binario.
 * @param c Ponteiro para o cabecalho.
 * @param busca Ponteiro para o registro que contem os parametros de busca.
 * @param amountOfBuscaFields Quantidade de parametros que fazem parte da busca.
 * @param att Ponteiro para o registro que contem as atualizacoes.
 * @param amountOfAttFields Quantidade de parametros que fazem parte da atualizacao.
*/
void searchUpdatePositions(FILE *bin, CABECALHO *c, REGISTRO *busca, int amountOfBuscaFields, REGISTRO *att, int amountOfAttFields)
{
    // Procurar por registros que contenham os campos do registro busca
    long fileSize = getFileSize(bin);
    REGISTRO aux;
    rewind(bin);
    readCabecalho(c, bin);

    while (ftell(bin) != fileSize)
    {
        if (!readSingleRegister(&aux, bin))
        {
            fseek(bin, aux.tamanhoRegistro, SEEK_CUR);
            continue;
        }

        if (validateBuscaWithRegisterRead(&aux, busca, amountOfBuscaFields))
        {
            // Pode substituir nesse registro aqui.
            // Verificar se esse registro possui o tamanho correto.

            // Registro que tera o conteudo da atualizacao
            REGISTRO newRegister;
            createNewRegisterWithUpdatedData(&newRegister, &aux, att);

            if (aux.tamanhoRegistro >= newRegister.tamanhoRegistro)
            {
                // Pode inserir aqui mesmo
                int amountOfTrashToWrite = aux.tamanhoRegistro - newRegister.tamanhoRegistro;
                newRegister.tamanhoRegistro = aux.tamanhoRegistro;

                //Voltar para a posicao no comeco do registro e escreve-lo.
                fseek(bin, -(newRegister.tamanhoRegistro + sizeof(char) + sizeof(int)), SEEK_CUR);
                writeBin(bin, &newRegister);
                writeTrash(bin, amountOfTrashToWrite);

                free(newRegister.nomeEstacao);
                free(newRegister.nomeLinha);
            }
            else
            {
                //Fazer a remocao logica. E inserir no arquivo reaproveitando os registros removidos.
                // Voltar para o comeco desse registro no arquivo bin
                fseek(bin, -(aux.tamanhoRegistro + sizeof(char) + sizeof(int)), SEEK_CUR);

                // Procurar o ultimo removido.
                // Se o ultimo removido for igual a -1, significa que nao houve registros removidos.
                // Atualizar o topoLista e remover esse registro.
                if (c->topoLista == -1)
                {
                    // Atualizar os campos relevantes.
                    int thisRegisterPosition = ftell(bin);
                    c->topoLista = thisRegisterPosition;

                    // Remover o registro.
                    aux.removido = REMOVIDO;
                    fwrite(&aux.removido, sizeof(char), 1, bin);
                    //Voltar para a posicao final do registro.
                    fseek(bin, (sizeof(int) + aux.tamanhoRegistro), SEEK_CUR);
                }
                else
                {
                    // Ja existe um registro removido.
                    long thisRegisterPosition = ftell(bin);

                    // O registro que sera removido deve receber no proxLista o valor do topoLista
                    // O topoLista deve ser atualizado com o byte offset desse registro que esta sendo removido.
                    aux.removido = REMOVIDO;
                    aux.proxLista = c->topoLista;

                    // Escreve o removido e o proxLista no registro.
                    fwrite(&aux.removido, sizeof(char), 1, bin);
                    fwrite(&aux.tamanhoRegistro, sizeof(int), 1, bin);
                    fwrite(&aux.proxLista, sizeof(long), 1, bin);

                    // Atualizar o topoLista.
                    c->topoLista = thisRegisterPosition;

                    // Voltar para a posicao atual do registro e ir pro proximo.
                    fseek(bin, (thisRegisterPosition), SEEK_SET);
                }

                // Inserir o registro atualizado no arquivo.
                long thisRegisterPosition = ftell(bin);

                // Busca e insercao do registro com reaproveitamento de registros logicamente removidos
                searchForOptimalPosition(&c->topoLista, &newRegister, bin);

                free(newRegister.nomeEstacao);
                free(newRegister.nomeLinha);

                // Voltar onde estava antes.
                fseek(bin, thisRegisterPosition, SEEK_SET);
            }
        }

        //Limpar os registros utilizados.
        free(aux.nomeEstacao);
        free(aux.nomeLinha);
    }
    rewind(bin);
    writeCabecalho(bin, c);
}
