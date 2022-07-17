/**
 * Autores: 
 * (11800970) Felipe de Alcantra Tome 
 * (11954374) Francisco Reis Nogueira 
*/

#include "parser.h"

/**
 * Converte uma String para Int.
 * @param str String contendo o valor que sera convertido para int.
 * @return Inteiro que representa o valor da string.
 * 
*/
int StringToInt(char *str)
{
    int strSize = strlen(str);
    int returnInt = 0;
    for (int i = 0; i < strSize; i++)
    {
        switch (str[i])
        {
        case '0':
            returnInt += 0;
            break;

        case '1':
            returnInt += 1;
            break;

        case '2':
            returnInt += 2;
            break;

        case '3':
            returnInt += 3;
            break;

        case '4':
            returnInt += 4;
            break;

        case '5':
            returnInt += 5;
            break;

        case '6':
            returnInt += 6;
            break;

        case '7':
            returnInt += 7;
            break;

        case '8':
            returnInt += 8;
            break;

        case '9':
            returnInt += 9;
            break;

        default:
            return -1;
        }

        if (i != strSize - 1)
            returnInt *= 10;
    }
    return returnInt;
}

/**
 * Adiciona um valor na struct REGISTRO.
 * 
 * @param r Ponteiro para a struct REGISTRO
 * @param lineToBeAdded String que contem o valor que sera adicionado na struct r.
 * @param columnCounter Inteiro que representa a posicao atual da coluna do arquivo csv.
 * @param isNull Representacao booleana para indicar se o valor que sera adicionado deve ser nulo.
 * @return 1 para sucesso, 0 para erro.
*/
int addPartOfLine(REGISTRO *r, char *lineToBeAdded, int columnCounter, int isNull)
{
    int number = 0;
    int lineSize = 0;

    // Muda os dois valores caso o valor a ser adicionado deve ser nulo.
    if (isNull)
    {
        number = NULLFIXO;
        // memset(lineToBeAdded, 0, strlen(lineToBeAdded)); // Limpa string
        // lineToBeAdded[0] = DELIMITADOR;
    }
    else if (columnCounter == 1 || columnCounter == 3)
    {
        // ColumnCounter == 1 eh NomeEstacao.
        // ColumnCounter == 3 eh NomeLinha.
        // Os dois sao strings.
        lineSize = strlen(lineToBeAdded);
    }
    else if (columnCounter < 8)
    {
        // Todo o resto sera um numero. columnCounter nao pode ser maior que 8.
        number = StringToInt(lineToBeAdded);
        if (number == -1) // Conversao falhou ou a funcao recebeu um valor incorreto.
            return 0;
    }
    else
        return 0;

    // Atribui os valores na struct
    switch (columnCounter)
    {
    case 0:
        // CodEstacao<int>
        r->codEstacao = number;
        break;

    case 1:
        // NomeEstacao<char*>
        r->nomeEstacao = (char *)malloc(sizeof(char) * lineSize + 1);
        strcpy(r->nomeEstacao, lineToBeAdded);
        break;

    case 2:
        // CodLinha<int>
        r->codLinha = number;
        break;

    case 3:
        // NomeLinha<char*>
        r->nomeLinha = (char *)malloc(sizeof(char) * lineSize + 1);
        strcpy(r->nomeLinha, lineToBeAdded);
        break;

    case 4:
        // CodProxEst<int>
        r->codProxEstacao = number;
        break;
    case 5:
        // DistanciaProxEst<int>
        r->distProxEstacao = number;
        break;
    case 6:
        // CodLinhaInteg<int>
        r->codLinhaIntegra = number;
        break;
    case 7:
        // CodEstacaoInteg<int>
        r->codEstIntegra = number;
        break;

    default:
        // se columnCounter nao esta entre [0,7] ha algo errado.
        return 0;
    }

    return 1;
}

/**
 * Interpreta uma unica linha do arquivo csv e adiciona ela em um registro.
 * @param r Ponteiro para a struct REGISTRO.
 * @param line String que contem uma toda uma linha do arquivo csv.
 * @return 1 para sucesso, 0 para erro.
*/
int parseLine(REGISTRO *r, char *line)
{
    int lineSize = strlen(line);

    // Variavel temporaria para concatenar os values da linha.
    char *tempLine = (char *)malloc(sizeof(char) * 64);
    memset(tempLine, 0, 64); // Limpa string.

    int tempLineCounter = 0;
    int columnsCounter = 0;
    int isNextNull = 0; // Representacao booleana

    // Concatena char por char na tempLine ate um dos breakpoint eh alcancado
    for (int i = 0; i <= lineSize; i++)
    {

        // Breakpoins que indicam se uma coluna foi percorrida
        if (line[i] == ',' || i == (lineSize - 2) || line[i] == '\0')
        {
            // tempLine ta vazia?
            if (!*tempLine)
                isNextNull = 1; // Entao ela recebera valor nulo

            tempLineCounter++;
            tempLine[tempLineCounter] = '\0';
            addPartOfLine(r, tempLine, columnsCounter, isNextNull);
            columnsCounter++;
            tempLineCounter = 0;
            isNextNull = 0;
            memset(tempLine, 0, 64); // Limpa string
        }
        else
        {
            tempLine[tempLineCounter] = line[i];
            tempLineCounter++;
        }
    }

    finalizeRegister(r);
    free(tempLine);

    return 1;
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
