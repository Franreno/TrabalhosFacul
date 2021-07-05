/*
    Author: Francisco Reis Nogueira
    github: https://github.com/Franreno

    Program to blink a LED in your computer using linux's sysref
    You must change LEDPath variable to match your LED path.

    The program gets an input from the command line
    e.g ./program Hello World -> program will blink 'hello world' in morse.

    if the input is not given, the program will blink 'zenith' in morse code.

    to compile:
    gcc -o blinkmorse blinkmorse.c
    then to run:
    ./blinkmorse <input>
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

//     !! Define your LED input here !!
#define LEDPath "/sys/class/leds/input4::capslock/brightness"


#define DIT 100000
#define DASH 300000

#define INTRA_SPACE 100001 // Gap between dits and dashes within a character
#define INTER_SPACE 300001 // Gap between characters of a word

int *charToMorse(char c)
{
    static int aux[6];
    switch (c)
    {
    case 'a':
        aux[0] = DIT;
        aux[1] = DASH;
        aux[2] = INTRA_SPACE;
        aux[3] = -1;
        return aux;
    
    case 'b':
        aux[0] = DASH;
        aux[1] = DIT;
        aux[2] = DIT;
        aux[3] = DIT;
        aux[4] = INTRA_SPACE;
        aux[5] = -1;
        return aux;
    
    case 'c':
        aux[0] = DIT;
        aux[1] = DIT;
        aux[2] = INTRA_SPACE;
        aux[3] = DIT;
        aux[4] = INTRA_SPACE;
        aux[5] = -1;
        return aux;
    
    case 'd':
        aux[0] = DASH;
        aux[1] = DIT;
        aux[2] = DIT;
        aux[3] = INTRA_SPACE;
        aux[4] = -1;
        return aux;
    
    case 'e':
        aux[0] = DIT;
        aux[1] = INTRA_SPACE;
        aux[2] = -1;
        return aux;
    
    case 'f':
        aux[0] = DIT;
        aux[1] = DASH;
        aux[2] = DIT;
        aux[3] = INTRA_SPACE;
        aux[4] = -1;
        return aux;
    
    case 'g':
        aux[0] = DASH;
        aux[1] = DASH;
        aux[2] = DIT;
        aux[3] = INTRA_SPACE;
        aux[4] = -1;
        return aux;
    
    case 'h':
        aux[0] = DIT;
        aux[1] = DIT;
        aux[2] = DIT;
        aux[3] = DIT;
        aux[4] = INTRA_SPACE;
        aux[5] = -1;
        return aux;
    
    case 'i':
        aux[0] = DIT;
        aux[1] = DIT;
        aux[2] = INTRA_SPACE;
        aux[3] = -1;
        return aux;
    
    case 'j':
        aux[0] = DASH;
        aux[1] = DIT;
        aux[2] = DASH;
        aux[3] = DIT;
        aux[4] = INTRA_SPACE;
        aux[5] = -1;
        return aux;
    
    case 'k':
        aux[0] = DASH;
        aux[1] = DIT;
        aux[2] = DASH;
        aux[3] = INTRA_SPACE;
        aux[4] = -1;
        return aux;
    
    case 'l':
        aux[0] = DASH;
        aux[1] = DASH;
        aux[2] = DASH;
        aux[3] = INTRA_SPACE;
        aux[4] = -1;
        return aux;
    
    case 'm':
        aux[0] = DASH;
        aux[1] = INTRA_SPACE;
        aux[2] = DASH;
        aux[3] = INTRA_SPACE;
        aux[4] = -1;
        return aux;
    
    case 'n':
        aux[0] = DASH;
        aux[1] = DIT;
        aux[2] = INTRA_SPACE;
        aux[3] = -1;
        return aux;
    
    case 'o':
        aux[0] = DIT;
        aux[1] = INTRA_SPACE;
        aux[2] = DIT;
        aux[3] = INTRA_SPACE;
        aux[4] = -1;
        return aux;
    
    case 'p':
        aux[0] = DIT;
        aux[1] = DIT;
        aux[2] = DIT;
        aux[3] = DIT;
        aux[4] = DIT;
        aux[5] = INTRA_SPACE;
        return aux;
    
    case 'q':
        aux[0] = DIT;
        aux[1] = DIT;
        aux[2] = DASH;
        aux[3] = DIT;
        aux[4] = INTRA_SPACE;
        aux[5] = -1;
        return aux;
    
    case 'r':
        aux[0] = DIT;
        aux[1] = INTRA_SPACE;
        aux[2] = DIT;
        aux[3] = DIT;
        aux[4] = INTRA_SPACE;
        aux[5] = -1;
        return aux;
    
    case 's':
        aux[0] = DIT;
        aux[1] = DIT;
        aux[2] = DIT;
        aux[3] = INTRA_SPACE;
        aux[4] = -1;
        return aux;
    
    case 't':
        aux[0] = DASH;
        aux[1] = INTRA_SPACE;
        aux[2] = -1;
        return aux;
    
    case 'u':
        aux[0] = DIT;
        aux[1] = DIT;
        aux[2] = DASH;
        aux[3] = INTRA_SPACE;
        aux[4] = -1;
        return aux;
    
    case 'v':
        aux[0] = DIT;
        aux[1] = DIT;
        aux[2] = DIT;
        aux[3] = DASH;
        aux[4] = INTRA_SPACE;
        aux[5] = -1;
        return aux;
    
    case 'w':
        aux[0] = DIT;
        aux[1] = DASH;
        aux[2] = DASH;
        aux[3] = INTRA_SPACE;
        aux[4] = -1;
        return aux;
    
    case 'x':
        aux[0] = DIT;
        aux[1] = DASH;
        aux[2] = DIT;
        aux[3] = DIT;
        aux[4] = INTRA_SPACE;
        aux[5] = -1;
        return aux;
    
    case 'y':
        aux[0] = DIT;
        aux[1] = DIT;
        aux[2] = INTRA_SPACE;
        aux[3] = DIT;
        aux[4] = DIT;
        aux[5] = INTRA_SPACE;
        return aux;
    
    case 'z':
        aux[0] = DIT;
        aux[1] = DIT;
        aux[2] = DIT;
        aux[3] = INTRA_SPACE;
        aux[4] = DIT;
        aux[5] = INTRA_SPACE;
        return aux;
    
    
    default:
        aux[0] = INTRA_SPACE;
        aux[1] = -1;
        return aux;
    }
}


int handleFile(FILE *ptr, char *state)
{
    ptr = fopen(LEDPath, "w");
    if (ptr == NULL)
    {
        printf("\t\t\tFile opening error...\n\t\t\tTry running with sudo.\n");
        return 1;
    }

    fwrite(state, sizeof(char), 1, ptr);
    fclose(ptr);

    return 0;
}


void doZenithMorse()
{
    FILE *LEDPointer = NULL;
    int zenithInMorse[19] = {DASH, DASH, DIT, DIT, // z
                             INTRA_SPACE, 
                             DIT,                  // e
                             INTRA_SPACE, 
                             DASH, DIT,            // n
                             INTRA_SPACE, 
                             DIT, DIT,             // i
                             INTRA_SPACE, 
                             DASH,                 // t
                             INTRA_SPACE, 
                             DIT, DIT, DIT, DIT};  // h

    // Blink "Zenith" in morse code
    for (int i = 0; i < 19; i++)
    { 
        if(zenithInMorse[i] != INTRA_SPACE)
           if(handleFile(LEDPointer, "1"))
		   return;
        
        usleep(zenithInMorse[i]); //sleep time between dits and dashes

        if(handleFile(LEDPointer, "0"))
		return;

        usleep(INTER_SPACE); //slep time between characters
    }

}

int main(int argc, char *argv[])
{
    printf("Led blinking start\n");
    FILE *LEDPointer = NULL;

    if (argc == 1)
    {
        printf("\tNo input given, blinking zenith in morse\n");
        doZenithMorse();
        return 0;
    }

    printf("\tBlinking your input!\n");
    for(int i=1; i<argc; i++)
    {
        printf("\t\tBlinking %s\n" , argv[i]);

        int **Elements = (int**)malloc(sizeof(int*) * (argc-1) );
        char *word = argv[i];
        int wordLenght = strlen(word);

        Elements[i] = (int*)malloc(sizeof(int) * wordLenght);
        for(int j=0; j<wordLenght; j++)
        {
            // Convert to lowercase
            if(word[j] >= 'A' && word[j] <= 'Z')
            {
                word[j]+=32;
            }

            Elements[j] = charToMorse(word[j]);

            //Blink for all characters in Elements[j]

            for(int k=0; k<6; k++) // 6 because it's the maximum size for the morse array
            {
                if(Elements[j][k] == -1)
                    break;

                if(Elements[j][k] != INTRA_SPACE)
                    if (handleFile(LEDPointer, "1"))
                        return 1; 
                
                usleep(Elements[j][k]); //sleep time between dits and dashes

                if (handleFile(LEDPointer, "0"))
                    return 1;

                usleep(INTER_SPACE); //slep time between characters
            }

        }
        
        // Free elements
        free(Elements);
    }

    //Turn LED back on
    // handleFIle(LEDPointer, "1");

    printf("Led blinking stopped\n");
    return 0;
}
