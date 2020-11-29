// fazer um que colocar em ordem
#include <stdio.h>
#include <string.h>


char* minify(char s[])
{
    for (int i = 0; s[i]!='\0'; i++) 
    {
        if(s[i] >= 'A' && s[i] <= 'Z') 
        {
            s[i] = s[i] + 32;
        }
    }

    return s;
}


int alfstrc(char str1[] , char str2[])
{
    // tres tipos de retorno, 0 se forem iguais, -1 se str1 tiver ordem alfabetica superior, 1 se str2 tiver ordem alfabetica superior
    int flag;
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    
    //transformar por precaucao todas as strings em minusculas.

    minify(str1);
    minify(str2);

    for (int i=0, j=0; i<len1 , j<len2; i++, j++)
    {

        //str 2 ta em ordem alfabetica
        if (str1[i] > str2[j])
        {
            flag = 1;
            return flag;
        }
        // str 1 ta em ordem
        else if(str1[i] < str2[j])
        {
            flag = -1;
            return flag;
        }
        // ainda indefinido
        else if(str1[i] == str2[j])
        {
            flag = 0;
        }
    }

    return flag;
}


void printStringsInOrder(char str[2][32], int flag)
{
    printf("in order: ");
    if(flag == -1)
        printf("%s , %s\n" , str[0] , str[1]);
    else if(flag == 1)
        printf("%s , %s\n" , str[1] , str[0]);
    else if(flag == 0)
        printf("%s == %s\n" , str[1] , str[0]);
}

int main()
{
                
    char str[2][32];
    
    scanf("%s %s" , str[0], str[1]);

    // organizar elas em ordem alfabetica.
    int flag;
    flag = alfstrc(str[0] , str[1]);
    
    printStringsInOrder(str, flag);
        
}