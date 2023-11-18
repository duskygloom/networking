#include "encoder.h"

#include <string.h>
#include <stdlib.h>

char *hex_to_bin(char ch)
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

int write_binary_data(FILE *binfile, FILE *hexfile) 
{
    int nbin = 0, ch;
    for (ch = getc(hexfile); IS_HEX(ch); ch = getc(hexfile), nbin += 4)
        fputs(hex_to_bin(ch), binfile);
    return nbin;
}

int write_data(FILE *datafile, FILE *binfile, int nbin, int nbit)
{
    int index = 0, i = 0, nsymbols = 0;
    if (nbin % nbit != 0) {
        fprintf(datafile, "%d ", index++);                  // index
        for (i = 0; i < nbit-nbin%nbit; ++i)                // extra zeroes
            fputc('0', datafile);
        for (i = 0; i < nbin%nbit; ++i)                     // remainder characters
            fputc(fgetc(binfile), datafile);
        fputc(' ', datafile);                               // delemeter space
        ++nsymbols;
    }
    for (; i < nbin; i += nbit) {
        fprintf(datafile, "%d ", index++);
        for (int j = 0; j < nbit; ++j)
            fputc(fgetc(binfile), datafile);
        fputc(' ', datafile);
        ++nsymbols;
    }
    return nsymbols;
}
