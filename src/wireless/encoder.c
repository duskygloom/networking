/*
    Read the file.
        Write the signal value into a file.
    Close the file.
*/

#include "encoder.h"
#include <stdio.h>
#include <string.h>

#define NUM_SAMPLES_PER_BIT 10

char *hex_to_bin(int ch)
{
    switch (ch) {
        case '0':
        default:
            return "0000";
        case '1':
            return "0001";
        case '2':
            return "0010";
        case '3':
            return "0011";
        case '4':
            return "0100";
        case '5':
            return "0101";
        case '6':
            return "0110";
        case '7':
            return "0111";
        case '8':
            return "1000";
        case '9':
            return "1001";
        case 'A':
        case 'a':
            return "1010";
        case 'B':
        case 'b':
            return "1011";
        case 'C':
        case 'c':
            return "1100";
        case 'D':
        case 'd':
            return "1101";
        case 'E':
        case 'e':
            return "1110";
        case 'F':
        case 'f':
            return "1111";
    }
}

void write_data(FILE *datafile, int ch)
{
    static int index = 0;
    char bits[5];
    strcpy(bits, hex_to_bin(ch));
    for (int bit = 0; bit < 4; ++bit, ++index) {
        fprintf(datafile, "%d %.4f ", 
            index,
            (float)(bits[bit] - '0')
        );
    }
}
