/**
 * Autores: 
 * (11800970) Felipe de Alcantra Tome 
 * (11954374) Francisco Reis Nogueira 
*/

#include <stdio.h>
#include "functions.h"

int main()
{
    int cmd;
    scanf("%d", &cmd);

    switch (cmd)
    {
    case 1:
        createTable();
        break;
    case 2:
        printEverything();
        break;
    case 3:
        selectWhere();
        break;
    case 4:
        deleteWhere();
        break;
    case 5:
        insertInto();
        break;
    case 6:
        updateTable();
    default:
        break;
    }
}
