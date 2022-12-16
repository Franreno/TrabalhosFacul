
/**
 * Autores: 
 * (11800970) Felipe de Alcantra Tome 
 * (11954374) Francisco Reis Nogueira 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"
#include "funcoesFornecidas.h"
#include "registro.h"

/**
 * Funcionalidade 1: Criacao do arquivo binario a partir de um arquivo csv.
*/
void createTable()
{
    char *csv, *bin;
    scanf("%ms", &csv);
    scanf("%ms", &bin);

    FILE *csvFile, *binFile;

    if (((csvFile = fopen(csv, "r")) == NULL) || ((binFile = fopen(bin, "wb")) == NULL))
    {
        printf("Falha no processamento do arquivo.\n");
        free(csv);
        free(bin);
        return;
    }

    if (!readAndWriteCSV(csvFile, binFile))
    {
        printf("Falha no processamento do arquivo.\n");
        free(csv);
        free(bin);
        return;
    }

    fclose(csvFile);
    fclose(binFile);

    binarioNaTela(bin);
    free(csv);
    free(bin);
}

/**
 * Funcionalidade 2: Print de todos os registros nao logicamente removidos.
*/
void printEverything()
{
    char *bin;
    scanf("%ms", &bin);

    FILE *binFile;

    binFile = fopen(bin, "rb");

    if (binFile == NULL)
    {
        printf("Registro inexistente.\n");
        free(bin);
        return;
    }

    if (!outputBinary(binFile))
    {
        printf("Registro inexistente.\n");
        free(bin);
        return;
    }

    fclose(binFile);

    free(bin);
}



/**
 * Interface para as funcionalidades 3 e 4, pois elas possuem muitos procedimentos em comum
 * @param operation Funcionalidade a ser exercida pela interface
 * @param binFile Ponteiro para arquivo que sera utilizado
*/
void funcHub(int operation, FILE *binFile)
{
    //O tamanho total do arquivo
    long fileSize = getFileSize(binFile);

    //Ler o cabecalho. Primeiros 4 campos.
    CABECALHO c;
    readCabecalho(&c, binFile);
    List *root = createList();

    REGISTRO r;

    //É feita a captação dos dados que serão utilizados para a busca
    int campoValor[8];
    char **stringValorCampo;
    stringValorCampo = (char **)malloc(sizeof(char *) * 8);
    int campos[8];
    int n = coletaDeDados(campoValor, stringValorCampo, campos);
    int flag = 0;

    //Inicialização dos parâmetros do cabeçalho
    int nroPares = 0;
    int nroEstacoes = 0;
    long ultimoRemovido = sizeof(char);
    List *alteracoes = createList();

    int lixo = 0;

    //Busca os registros, caso nao seja logicamente removido retorna 1
    while (buscaRegistro(binFile, fileSize, &r, stringValorCampo, campoValor, n, campos, root, &nroPares, &nroEstacoes, &ultimoRemovido))
    {
        switch (operation)
        {
        case 1:
            //Funcionalidade 3
            printRegistro(&r);
            free(r.nomeEstacao);
            free(r.nomeLinha);
            break;

            //Funcionalidade 4
        case 2:            
            //É feita uma lista de registros a serem removidos
            insertEnd(alteracoes, &lixo, &lixo, r.nomeEstacao, r.codEstacao, r.codProxEstacao, ftell(binFile) - r.tamanhoRegistro - sizeof(char) - sizeof(int));
            free(r.nomeEstacao);
            free(r.nomeLinha);
            break;
        }

        flag = 1;

        // Verificar se chegou no fim do arquivo.
        if (ftell(binFile) == fileSize)
            break;
    }

    if (!flag && operation == 1)
        printf("Registro inexistente.\n");//Nao encontrou nenhum registro e esta na func. 3
    if (flag)//Encontrou o registro
    {
        fseek(binFile, 0, SEEK_SET);
        c.status = INCONSISTENTE;
        writeCabecalho(binFile, &c);
        
        //Faz a exclusão de todos  os registros da lista
        deleteRegistros(binFile, alteracoes, ultimoRemovido);
        
        //Atualiza o cabeçalho para status valido e com o nro certo e pares e est.
        fseek(binFile, 0, SEEK_SET);
        c.nroEstacoes = nroEstacoes;
        c.nroParesEstacao = nroPares;
        c.status = CONSISTENTE;
        fwrite(&c.status, 1, sizeof(char), binFile);
        fseek(binFile, sizeof(long), SEEK_CUR);
        fwrite(&(c.nroEstacoes), 1, sizeof(int), binFile);
        fwrite(&(c.nroParesEstacao), 1, sizeof(int), binFile);
    }

    for (int i = 0; i < n; i++)
    {
        if (campos[i] > 6)
            free(stringValorCampo[i]);//libera a memoria utilizada
    }
    free(stringValorCampo);
    deleteList(alteracoes);//libera as listas
    deleteList(root);
}

/**
 * Funcionalidade 3: print de todos os registros que atendem a um critério de busca
*/
void selectWhere()
{
    char *bin;
    scanf("%ms", &bin);

    FILE *binFile;
    if (((binFile = fopen(bin, "rb")) == NULL))//Abertura do arquivo
    {
        printf("Falha no processamento do arquivo.");
        return;
    }

    funcHub(1, binFile);//Chamada da interface
    fclose(binFile);
    free(bin);
}

/**
 * Funcionalidade 4: Exclusao de n registros logicamente
*/
void deleteWhere()
{
    char *bin;
    scanf("%ms", &bin);

    FILE *binFile;
    if (((binFile = fopen(bin, "r+b")) == NULL))//Abertura do arquivo
    {
        printf("Falha no processamento do arquivo.");
        return;
    }

    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
        funcHub(2, binFile);//n chamadas da interface de acordo com o numero de exclusoes
    if (binFile)
    {
        fclose(binFile);
        binarioNaTela(bin);
    }
    free(bin);
}

/**
 * Funcionalidade 5. Insercao de N registros no arquivo binario.
*/
void insertInto()
{
    char *bin;
    scanf("%ms", &bin);

    FILE *binFile;

    if ((binFile = fopen(bin, "rb+")) == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        free(bin);
        return;
    }

    insertNTimes(binFile);

    fclose(binFile);
    binarioNaTela(bin);
    free(bin);
}

/**
 * Funcao que coleta os inputs e chama a funcao que realiza o algoritmo de atualizar os dados dos registros
 * @param bin Ponteiro para o arquivo binario.
*/
void updateNTimes(FILE *bin)
{
    int amountOfRegistersToBeUpdated;
    int amountOfBuscaFields;
    int amountOfAttFields;
    scanf("%d", &amountOfRegistersToBeUpdated);

    CABECALHO c;
    readCabecalho(&c, bin);
    c.status = INCONSISTENTE;

    REGISTRO busca, att;
    for (int i = 0; i < amountOfRegistersToBeUpdated; i++)
    {
        // Pega os inputs de busca e atualizacoes
        scanUpdateInputs(&busca, &amountOfBuscaFields, &att, &amountOfAttFields);

        // Procura, atualiza e insere os registros de acordo com os criterios de busca
        searchUpdatePositions(bin, &c, &busca, amountOfBuscaFields, &att, amountOfAttFields);

        free(busca.nomeEstacao);
        free(busca.nomeLinha);
        free(att.nomeEstacao);
        free(att.nomeLinha);
        cleanUpdateRegister(&busca);
        cleanUpdateRegister(&att);
    }

    rewriteCabecalho(&c, bin);
}

/**
 * Funcionalidade 6: Atualizar N registros de acordo com os criterios de busca e 
 * atualizacoes.
*/
void updateTable()
{
    char *bin;
    scanf("%ms", &bin);

    FILE *binFile;

    if ((binFile = fopen(bin, "rb+")) == NULL)
    {
        printf("Falha no processamento do arquivo.\n");
        free(bin);
        return;
    }

    updateNTimes(binFile);

    fclose(binFile);
    binarioNaTela(bin);

    free(bin);
}
