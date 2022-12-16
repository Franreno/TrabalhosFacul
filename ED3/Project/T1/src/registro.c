/**
 * Autores: 
 * (11800970) Felipe de Alcantra Tome 
 * (11954374) Francisco Reis Nogueira 
*/

#include "registro.h"

/*----------------------------------------------------------------*/

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

/**
 * Finaliza a criacao de um registro qualquer. Atribui o valor de NAOREMOVIDO, proxLista nulo 
 * e calcula o tamanho do registro.
 * @param r Ponteiro para o registro.
*/
void finalizeRegister(REGISTRO *r)
{
    // Finalizacao da struct
    r->removido = NAOREMOVIDO;
    r->proxLista = -1;
    // Byte offset do registro
    // strlen+1 pra contar com o delimitador que sera inserido depois.
    r->tamanhoRegistro = sizeof(r->proxLista) + sizeof(r->codEstacao) + (strlen(r->nomeEstacao) + 1) + sizeof(r->codLinha) + (strlen(r->nomeLinha) + 1) + sizeof(r->codProxEstacao) + sizeof(r->distProxEstacao) + sizeof(r->codLinhaIntegra) + sizeof(r->codEstIntegra);
}

/**
 * Pega os inputs de tamanho fixo e variaveis para a funcionalidade 5 (insercao). 
 * @param r Ponteiro para o registro no qual sera feita as atribuicoes dos inputs.
*/
int scanInsertInputs(REGISTRO *r)
{
    char *tempLine = (char *)malloc(sizeof(char) * 64);

    // codEstacao
    scanIntegerInputs(&r->codEstacao, &tempLine);

    // nomeEstacao
    scanStringInputs(&r->nomeEstacao, &tempLine);

    // codLinha
    scanIntegerInputs(&r->codLinha, &tempLine);

    // nomeLinha
    scanStringInputs(&r->nomeLinha, &tempLine);

    // codProxEstacao
    scanIntegerInputs(&r->codProxEstacao, &tempLine);

    // distProxEstacao
    scanIntegerInputs(&r->distProxEstacao, &tempLine);

    // codLinhaIntegra
    scanIntegerInputs(&r->codLinhaIntegra, &tempLine);

    // codEstIntegra
    scanIntegerInputs(&r->codEstIntegra, &tempLine);

    // Finalizar o registro
    finalizeRegister(r);

    free(tempLine);

    return 1;
}

/**
 * Funcao que atribui os inputs de busca e atualizacao para a funcionalidade 6 (Insercao).
 * @param busca Ponteiro para o registro de busca.
 * @param amountOfBuscaFields Quantidade de parametros de busca.
 * @param att Ponteiro para o registro de atualizacao.
 * @param amountOfAttFields Quantidade de parametros de atualizacao.
*/
int scanUpdateInputs(REGISTRO *busca, int *amountOfBuscaFields, REGISTRO *att, int *amountOfAttFields)
{
    createUpdateRegisterInputs(busca, amountOfBuscaFields);
    createUpdateRegisterInputs(att, amountOfAttFields);
    return 1;
}

/*----------------------------------------------------------------*/

/**
 * Le um arquivo .csv e escreve um arquivo .bin. 
 * @param csv Ponteiro para o arquivo aberto .csv
 * @param bin Ponteiro para o arquivo aberto .bin
 * @return 1 para sucesso, 0 para erro.
*/
int readAndWriteCSV(FILE *csv, FILE *bin)
{
    CABECALHO c;
    REGISTRO r;

    // Linha para pegar os valores do arquivo
    char *line = (char *)malloc(sizeof(char) * 128);

    // Escreve o comeco do cabecalho.
    c.status = INCONSISTENTE;
    c.topoLista = -1;
    c.nroEstacoes = 0;
    c.nroParesEstacao = 0;
    List *root = createList();

    writeCabecalho(bin, &c);

    // Pega tamanho do arquivo para ser percorrido
    long fileSize = getFileSize(csv);

    // Descarta a primeira linha (Header do csv)
    fgets(line, 128, csv);
    // int i = 0;
    while (ftell(csv) != fileSize)
    {
        // Pega uma linha inteira
        fgets(line, 128, csv);

        // Interpreta a linha e cria um registro correspondente a essa linha
        if (!parseLine(&r, line))
            return 0;

        //Escreve esse registro no arquivo binario
        writeBin(bin, &r);

        //Adiciona esses valores na lista
        insertEnd(root, &c.nroEstacoes, &c.nroParesEstacao, r.nomeEstacao, r.codEstacao, r.codProxEstacao, ftell(bin) - r.tamanhoRegistro - sizeof(int) - sizeof(char));

        // Limpa os valores alocados dinamicamente do registro
        free(r.nomeEstacao);
        free(r.nomeLinha);
    }

    c.status = CONSISTENTE;
    // Volta o ponteiro do arquivo para o comeco.
    rewind(bin);
    // Reescreve o cabecalho com os novos valores encontrados.
    writeCabecalho(bin, &c);

    free(line);

    //Libera a lista
    deleteList(root);

    return 1;
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

/*----------------------------------------------------------------*/

/**
 * Coleta de dados relevantes para realização de buscas no arquivo,
 * retorna o nro de campos utilizados como criterio e seus valores
 * @param campoValor Vetor de valores que serao utilizados como criterio de busca
 * @param stringCampoValor Vetor de strings que serao utilizadas como criterio de busca
 * @param campos Quais campos serao de interesse, "enderecados" numericamente
 * @return n Retorna o numero de campos que serao utilizados como criterio de busca
*/
int coletaDeDados(int *campoValor, char **stringValorCampo, int *campos)
{
    int n;
    char *campo;
    scanf("%d\n", &n);

    //Checa quais campos serao utilizados como criterio
    for (int i = 0; i < n; i++)
    {
        scanf("%ms", &campo);
        if (!strcmp("codEstacao", campo))
            campos[i] = 1;
        if (!strcmp("codLinha", campo))
            campos[i] = 2;
        if (!strcmp("codProxEstacao", campo))
            campos[i] = 3;
        if (!strcmp("distProxEstacao", campo))
            campos[i] = 4;
        if (!strcmp("codLinhaIntegra", campo))
            campos[i] = 5;
        if (!strcmp("codEstIntegra", campo))
            campos[i] = 6;
        if (!strcmp("nomeEstacao", campo))
            campos[i] = 7;
        if (!strcmp("nomeLinha", campo))
            campos[i] = 8;

        //Checa a natureza dos campos, se eles sao numericos ou strings e preenche os valores
        if (campos[i] > 0 && campos[i] <= 6)
            scanf("%d", &(campoValor[i]));
        else
        {
            stringValorCampo[i] = (char *)malloc(sizeof(char) * 64);
            scan_quote_string(stringValorCampo[i]);
        }
        memset(campo, 0, strlen(campo));
        free(campo);
    }
    return n;
}

/**
 * Busca registros presentes no arquivo binario de acordo com um numero especifico de critérios
 * @param bin Ponteiro para arquivo de interesse
 * @param fileSize Tamanho do arquivo supracitado
 * @param r Registro que sera utilizado para ler e processar todos os registros do arquivo
 * @param stringValorCampo Vetor de strings de interesse
 * @param campoValor Vetor de valores de interesse
 * @param n Numero de campos que estao sendo utilizados como criterio de busca
 * @param campos Campos que serao utilizados como criterio de busca, enderecados numericamente
 * @param total Lista de todos os registros do arquivo
 * @param nroPares Nro de pares presentes no todo do arquivo de interesse
 * @param nroEstacoes Nro de estacoes unicas presentes no arquivo de interesse
 * @param ultimoRemovido Ultimo registro removido logicamente, de acordo com a logica de lista este seria o fim
 * @return flag Indica se o registro de interesse foi encontrado ou nao dentro desta iteracao
*/
int buscaRegistro(FILE *bin, long fileSize, REGISTRO *r, char **stringValorCampo, int *campoValor, int n, int *campos, List *total, int *nroPares, int *nroEstacoes, long *ultimoRemovido)
{
    int flag;
    //Percorre todo arquivo binario
    while (ftell(bin) != fileSize)
    {
        if (readSingleRegister(r, bin))
        {
            flag = 1;
            for (int i = 0; i < n; i++)
            {
                //Faz a comparacao dos campos de interesse, caso nao atendam ao criterio de busca a flag sera anulada
                switch (campos[i])
                {
                case 1:
                    if (campoValor[i] != r->codEstacao)
                        flag = 0;
                    break;
                case 2:
                    if (campoValor[i] != r->codLinha)
                        flag = 0;
                    break;
                case 3:
                    if (campoValor[i] != r->codProxEstacao)
                        flag = 0;
                    break;
                case 4:
                    if (campoValor[i] != r->distProxEstacao)
                        flag = 0;
                    break;
                case 5:
                    if (campoValor[i] != r->codLinhaIntegra)
                        flag = 0;
                    break;
                case 6:
                    if (campoValor[i] != r->codEstIntegra)
                        flag = 0;
                    break;
                case 7:
                    if (strcmp(stringValorCampo[i], r->nomeEstacao))
                        flag = 0;
                    break;
                case 8:
                    if (strcmp(stringValorCampo[i], r->nomeLinha))
                        flag = 0;
                    break;
                }
            }
            if (flag)
                return flag;

            //Caso o registro tenha sido encontrado as demais operacoes sao desnecessarias, caso ele nao seja de interesse ele entra para a lista de todos os registros correntes, pois nao sera alterado ou excluido
            insertEnd(total, nroEstacoes, nroPares, r->nomeEstacao, r->codEstacao, r->codProxEstacao, ftell(bin) - r->tamanhoRegistro - sizeof(char) - sizeof(int));
            free(r->nomeEstacao);
            free(r->nomeLinha);
        }
        else
        {
            //Se o registro for removido e for o ultimo da lista seu endereco é de interesse
            if (r->proxLista == -1)
                *ultimoRemovido = ftell(bin);
            fseek(bin, r->tamanhoRegistro, SEEK_CUR);
        }
    }
    return flag;
}

/*----------------------------------------------------------------*/

/**
 * Funcao de procura pelo melhor lugar para a insercao de um registro, com aproveitamento de registros removidos.
 * @param topoLista referencia ao valor do cabecalho topoLista.
 * @param r Ponteiro para o registro que sera escrito.
 * @param bin Ponteiro para o arquivo binario.
*/
int searchForOptimalPosition(long *topoLista, REGISTRO *r, FILE *bin)
{
    long ultimaPosicaoLida = 0;
    long posicaoAtualLida = (*topoLista);

    if ((*topoLista) == -1)
    {
        // Nao ha registros removidos.
        // Registro deve ser inserido no final.
        fseek(bin, 0, SEEK_END);
        writeBin(bin, r);
    }
    else
    {
        // Ha registros removidos.
        // Vai para o topo da Lista.
        // Registro auxiliar para as manipulacoes do arquivo
        REGISTRO aux;
        fseek(bin, (*topoLista), SEEK_SET);

        // Ler um registro removido
        int status = readFromRemovedRegister(&aux, bin, &r->tamanhoRegistro);
        while (!status)
        {
            // Registro que sera inserido nao cabe no registro que foi lido.
            // Ir para a proxima posicao da lista.
            ultimaPosicaoLida = posicaoAtualLida;
            posicaoAtualLida = aux.proxLista;
            fseek(bin, aux.proxLista, SEEK_SET);
            status = readFromRemovedRegister(&aux, bin, &r->tamanhoRegistro);
        }

        // Chegou no final da lista.
        // Insere no fim.
        if (status == -1)
        {
            fseek(bin, 0, SEEK_END);
            writeBin(bin, r);
        }
        // Achou um registro que cabe o registro que sera inserido.
        else
        {
            //  Quantidades de bytes que deverao ser preenchidos para ocupacao do espaco.
            int ammountOfBytesToFill = aux.tamanhoRegistro - r->tamanhoRegistro;
            // O tamanho do registro que sera inserido continua sendo o mesmo do que foi lido.
            r->tamanhoRegistro = aux.tamanhoRegistro;

            // Se a posicao atual ainda continua igual ao topoLista,
            // significa que esta sendo inserido no primeiro registro da lista
            // assim o topoLista deve mudar.
            if ((posicaoAtualLida == (*topoLista)))
                (*topoLista) = aux.proxLista;
            else
            // Registro foi inserido no meio da lista.
            // Deve ser linkado a ultimaPosicaoLida com a proxLista.
            {
                long placeWhereIAm = ftell(bin);

                // Vai para o lugar onde devera ser escrita a nova proxLista.
                // Pula os valores do removido e do tamanhoRegistro.
                fseek(bin, ultimaPosicaoLida + sizeof(char) + sizeof(int), SEEK_SET);
                fwrite(&aux.proxLista, sizeof(long), 1, bin);

                // Volta pro lugar onde estava antes.
                fseek(bin, placeWhereIAm, SEEK_SET);
            }

            // Escreve os inteiros
            writeIntegerAtBinary(bin, r);
            // Escreve as strings
            writeStringAtBinary(bin, r);
            // Preenche o espaco vazio
            writeTrash(bin, ammountOfBytesToFill);

            // Libera espaco utilizado pelo ponteiro auxiliar
            free(aux.nomeEstacao);
            free(aux.nomeLinha);
        }
    }

    return 1;
}

/**
 * Insercao de N novos registros no arquivo binario. Reaproveita os registros ja removidos.
 * @param bin Ponteiro para o arquivo binario.
*/
int insertNTimes(FILE *bin)
{
    int amountOfRegistersToBeInserted;
    scanf("%d", &amountOfRegistersToBeInserted);

    REGISTRO r;

    CABECALHO c;
    readCabecalho(&c, bin);
    c.status = INCONSISTENTE;

    for (int i = 0; i < amountOfRegistersToBeInserted; i++)
    {
        // Pega os inputs do registro que sera inserido
        scanInsertInputs(&r);
        // Procura uma posicao para a insercao do registro
        searchForOptimalPosition(&c.topoLista, &r, bin);
        free(r.nomeEstacao);
        free(r.nomeLinha);
    }

    // Reescrever o cabecalho.
    rewriteCabecalho(&c, bin);

    return 1;
}

/**
 * Cria um novo registro a partir de um registro auxiliar, que foi lido, e um registro de atualizacao. 
 * Pega os valores do registro de atualizacao e atribui aqueles que nao sao nulos no registro de newRegister. 
 * Caso o valor seja nulo eh atribuido ao novo registro os valores do registro aux.
 * @param newRegister Ponteiro para o novo registro que esta sendo criado.
 * @param aux Ponteiro para o registro que foi lido.
 * @param att Ponteiro para o registro de atualizacao.
*/
void createNewRegisterWithUpdatedData(REGISTRO *newRegister, REGISTRO *aux, REGISTRO *att)
{
    updateIntegersAtNewRegisterInsert(&newRegister->codEstacao, &aux->codEstacao, &att->codEstacao);

    updateIntegersAtNewRegisterInsert(&newRegister->codLinha, &aux->codLinha, &att->codLinha);

    updateIntegersAtNewRegisterInsert(&newRegister->codProxEstacao, &aux->codProxEstacao, &att->codProxEstacao);

    updateIntegersAtNewRegisterInsert(&newRegister->distProxEstacao, &aux->distProxEstacao, &att->distProxEstacao);

    updateIntegersAtNewRegisterInsert(&newRegister->codLinhaIntegra, &aux->codLinhaIntegra, &att->codLinhaIntegra);

    updateIntegersAtNewRegisterInsert(&newRegister->codEstIntegra, &aux->codEstIntegra, &att->codEstIntegra);

    updateStringsAtRemovedInsert(&newRegister->nomeEstacao, &aux->nomeEstacao, &att->nomeEstacao);

    updateStringsAtRemovedInsert(&newRegister->nomeLinha, &aux->nomeLinha, &att->nomeLinha);

    finalizeRegister(newRegister);
}

/*
 * Faz a exclusão de uma lista encadeada de registros
 * @param bin Arquivo de interesse
 * @param alteracoes Lista dos registros que deverao ser excluidos
 * @param ultimoRemovido Fim da lista de registros excluidos
*/

void deleteRegistros(FILE *bin, List *alteracoes, long ultimoRemovido)
{
    long aux = ultimoRemovido;
    node *ptr = *alteracoes;
    char remov = '1';
    while (ptr != NULL)
    {
        fseek(bin, ptr->posRegistro, SEEK_SET);
        //Indica o registro como logicamente removido
        fwrite(&remov, 1, sizeof(char), bin);
        fseek(bin, aux, SEEK_SET);
        //Registra a posicao da lista que antecede esse registro
        fwrite(&(ptr->posRegistro), 1, sizeof(long), bin);
        aux = ptr->posRegistro + sizeof(char) + sizeof(int);
        ptr = ptr->next;
    }
}

