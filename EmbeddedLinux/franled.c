/*
    Program to blink a beaglebone LED's to say 'zenith'
    in morse code.
*/

#include <stdio.h>
#include <unistd.h>

#define LEDPath = "/sys/class/leds/beaglebone:green:usr2/brightness";
#define DIT 100000
#define DASH 300000

#define INTRA_SPACE 100001 // Gap between dits and dashes within a character
#define INTER_SPACE 300001 // Gap between characters of a word

int handleType(FILE *ptr, char *state)
{
    ptr = fopen(LEDPath, "w");
    if (ptr == NULL)
    {
        printf("File opening error...\n ");
        return 1;
    }

    fwrite(state, sizeof(char), 1, ptr);
    fclose(ptr);

    return 0;
}

int main()
{
    printf("Led blinking start\n");
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
            handleType(LEDPointer, "1");
        
        usleep(zenithInMorse[i]); //sleep time between dits and dashes

        handleType(LEDPointer, "0");

        usleep(INTER_SPACE); //slep time between characters
    }

    //Turn LED back on
    handleType(LEDPointer, "1");

    printf("Led blinking stopped\n");
    return 0;
}