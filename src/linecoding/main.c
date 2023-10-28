#include "encoder.h"
#include <stdio.h>

#define DATAFILE "datafile.dat"

int main(int argc, char *argv[])
{
    FILE *hexfile;
    if (!(argc > 1 && (hexfile = fopen(argv[1], "r")))) {
        puts("The first argument must be a valid file name.");
        return 1;
    }
    FILE *datafile;
    if (!(datafile = fopen(DATAFILE, "w"))) {
        printf("Failed to write %s.\n", DATAFILE);
        return 2;
    }
    int ch;
    while (is_hex(ch = getc(hexfile)))
        write_data(datafile, ch);
    fclose(datafile);
    fclose(hexfile);
    return 0;
}
