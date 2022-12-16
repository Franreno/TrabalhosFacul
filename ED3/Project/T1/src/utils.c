/**
 * Autores: 
 * (11800970) Felipe de Alcantra Tome 
 * (11954374) Francisco Reis Nogueira 
*/

#include "utils.h"

/**
 * Pega o input, converte ele a um valor inteiro e atribui esse valor a um ponteiro 
 * de referencia.
 * @param value Ponteiro de referencia no qual sera utilizado guardar o input.
 * @param str Ponteiro de referencia para a string que eh utilizado para pegar o valor bruto do input.
*/
void scanIntegerInputs(int *value, char **str)
{
    scanf("%s", *str);
    if (isNull(*str))
        *value = -1;
    else
        *value = StringToInt(*str);
    memset(*str, 0, 64);
}

/**
 * Pega o input de uma string entre aspas e atribui o seu valor a uma string de referencia.
 * @param strValue Ponteiro de referencia da string que guardara o valor do input.
 * @param auxStr Ponteiro de referencia para a string que sera utilizada para pegar o input.
*/
void scanStringInputs(char **strValue, char **auxStr)
{
    scan_quote_string(*auxStr);

    // String ta vazia, colocar o valor nulo.
    if ((!**auxStr))
    {
        (*strValue) = (char *)malloc(sizeof(char) * 2);
        (*strValue)[0] = '\0';
    }
    else
    {
        // Alocar a memoria para a string.
        int size = strlen(*auxStr);
        (*strValue) = (char *)malloc(sizeof(char) * size + 1);
        strcpy((*strValue), (*auxStr));
        (*strValue)[size] = '\0';
    }
    memset((*auxStr), 0, 64);
}

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

/**
 * Limpa o registro utilizado para a busca e atualizacao.
 * @param r Ponteiro para o registro de busca/atualizacao.
*/
void cleanUpdateRegister(REGISTRO *r)
{
    r->codEstacao = -1;
    r->codLinha = -1;
    r->codProxEstacao = -1;
    r->distProxEstacao = -1;
    r->codLinhaIntegra = -1;
    r->codEstIntegra = -1;
    r->nomeEstacao = NULL;
    r->nomeLinha = NULL;
}

/**
 * Valida os valores de string. Caso alguma string nao seja utilizada no 
 * registro de busca/atualizacao eh alocado uma memoria e atribuido um valor que 
 * eh interpretado como nulo.
 * @param r Ponteiro para o registro de busca/atualizacao
*/
void validateUpdateStrings(REGISTRO *r)
{
    if (r->nomeEstacao == NULL)
    {
        (r->nomeEstacao) = (char *)malloc(sizeof(char) * 2);
        (r->nomeEstacao)[0] = '\0';
    }

    if (r->nomeLinha == NULL)
    {
        (r->nomeLinha) = (char *)malloc(sizeof(char) * 2);
        (r->nomeLinha)[0] = '\0';
    }
}

/**
 * Pega o index a partir de um array dos campos que sao utilizados na busca/atualizacao.
 * Dependendo do index eh atribuido a um registro o valor lido pelo input.
*/
int scanCampoInput()
{
    const char *headerFields[8] = {"codEstacao\0", "nomeEstacao\0", "codLinha\0", "nomeLinha\0", "codProxEstacao\0", "distProxEstacao\0", "codLinhaIntegra\0", "codEstacaoIntegra\0"};
    int amountofHeaderFields = 8;

    char *campo;
    scanf("%ms", &campo);

    // Procura qual eh o campo.
    // Retorna valor entre [1,8]
    for (int i = 1; i <= amountofHeaderFields; i++)
    {
        if (!strcmp(campo, headerFields[i - 1]))
        {
            free(campo);
            return i;
        }
    }

    free(campo);
    return 0;
}

/**
 * Atribui o valor que sera lido no campo especificado no input.
 * @param r Ponteiro para o registro de busca/atualizacao.
 * @param position [1,8] Simbolizando os varios campos do registro. 
*/
int applyValueAtRegister(REGISTRO *r, int position)
{
    char *tempLine = (char *)malloc(sizeof(char) * 64);

    switch (position)
    {
    case 1:
        // codEstacao<int>
        scanIntegerInputs(&r->codEstacao, &tempLine);
        break;
    case 2:
        // nomeEstacao<char *>
        scanStringInputs(&r->nomeEstacao, &tempLine);
        break;
    case 3:
        // codLinha<int>
        scanIntegerInputs(&r->codLinha, &tempLine);
        break;
    case 4:
        // nomeLinha<char *>
        scanStringInputs(&r->nomeLinha, &tempLine);
        break;
    case 5:
        // codProxEstacao<int>
        scanIntegerInputs(&r->codProxEstacao, &tempLine);
        break;
    case 6:
        // distProxEstacao<int>
        scanIntegerInputs(&r->distProxEstacao, &tempLine);
        break;
    case 7:
        // codLinhaIntegra<int>
        scanIntegerInputs(&r->codLinhaIntegra, &tempLine);
        break;
    case 8:
        // codEstIntegra<int>
        scanIntegerInputs(&r->codEstIntegra, &tempLine);
        break;
    default:
        break;
    }

    free(tempLine);
    return 1;
}

/**
 * Cria e atribui os valores para os registros de busca e atualizacao.
 * @param r Ponteiro para o registro de busca/atualizacao.
 * @param amountOfFields Quantidade de campos que serao utilizados no registro de busca/atualizacao.
*/
void createUpdateRegisterInputs(REGISTRO *r, int *amountOfFields)
{
    cleanUpdateRegister(r);

    scanf("%d", amountOfFields);

    for (int i = 0; i < (*amountOfFields); i++)
    {
        // Pegar o input do campo
        int campoPosition = scanCampoInput();
        if (!campoPosition)
            return;

        applyValueAtRegister(r, campoPosition);
    }

    validateUpdateStrings(r);
}

/**
 * Valida os campos inteiros entre dois registros diferentes.
 * @param read Ponteiro de referencia para o campo inteiro do registro que foi lido.
 * @param search Ponteiro de referencia para o campo inteiro do registro de busca.
*/
int validateIntegersBuscaFields(int *read, int *search)
{
    if ((*search) != -1)
    {
        if ((*read) == (*search))
            return 1;
    }

    return 0;
}

/**
 * Valida os campos de string entre dois registros diferentes.
 * @param read Ponteiro de referencia para o campo string do registro que foi lido.
 * @param search Ponteiro de referencia para o campo string do registro de busca.
*/
int validateStringsBuscaFields(char **read, char **search)
{
    if ((*search)[0] != '\0')
    {
        if (!strcmp((*read), (*search)))
            return 1;
    }

    return 0;
}

/**
 * Valida o registro lido com os valores do registro de busca. O registro lido deve ter ao menos 
 * `amountOfBuscaFields` campos cujo valor eh igual aos campos do registro de busca. Se o campo de busca 
 * eh nulo significa que esse campo nao eh utilizado como padrao de busca.
 * @param aux Ponteiro para o registro que foi lido.
 * @param busca Ponteiro para o registro de busca.
 * @param amountOfBuscaFields Quantidade minima de campos que `aux` deve ter em comum com `busca`. 
*/
int validateBuscaWithRegisterRead(REGISTRO *aux, REGISTRO *busca, int amountOfBuscaFields)
{
    // Contar quantos campos nao sao nulos.
    int counter = 0;

    // Verificar os registros
    counter += validateIntegersBuscaFields(&aux->codEstacao, &busca->codEstacao);

    counter += validateIntegersBuscaFields(&aux->codLinha, &busca->codLinha);

    counter += validateIntegersBuscaFields(&aux->codProxEstacao, &busca->codProxEstacao);

    counter += validateIntegersBuscaFields(&aux->distProxEstacao, &busca->distProxEstacao);

    counter += validateIntegersBuscaFields(&aux->codLinhaIntegra, &busca->codLinhaIntegra);

    counter += validateIntegersBuscaFields(&aux->codEstIntegra, &busca->codEstIntegra);

    counter += validateStringsBuscaFields(&aux->nomeEstacao, &busca->nomeEstacao);

    counter += validateStringsBuscaFields(&aux->nomeLinha, &busca->nomeLinha);

    if (counter >= amountOfBuscaFields)
        return 1;
    else
        return 0;
}

/**
 * Atribui a um destino o valor original ou o valor atualizado de registros lidos/atualizados.
 * @param dest Ponteiro de referencia para o valor inteiro do novo registro.
 * @param originalSource Ponteiro de referencia para o valor inteiro original do registro lido.
 * @param updatedSource Ponteiro de referencia para o valor inteiro do registro de atualizacao.
*/
void updateIntegersAtNewRegisterInsert(int *dest, int *originalSource, int *updatedSource)
{
    if ((*updatedSource) != -1)
        (*dest) = (*updatedSource);
    else
        (*dest) = (*originalSource);
}

/**
 * Atribui a um destino o valor original ou o valor atualizado dos registros lidos/atualizados.
 * @param dest Ponteiro de referencia para o valor String do novo registro.
 * @param originalSource Ponteiro de referencia para o valor String original do registro lido.
 * @param updatedSource Ponteiro de referencia para o valor String do registro de atualizacao.
*/
void updateStringsAtRemovedInsert(char **dest, char **originalSource, char **updatedSource)
{
    int stringSize;
    char **stringToUse;
    if ((*updatedSource)[0] != '\0')
        stringToUse = updatedSource;
    else
        stringToUse = originalSource;

    stringSize = strlen(*stringToUse) + 1;
    (*dest) = (char *)malloc(sizeof(char) * stringSize);
    strcpy((*dest), (*stringToUse));
}