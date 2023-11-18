#include "encoder.h"
#include "noise_addition.h"
#include <stdio.h>

#define NUM_SAMPLES_PER_BIT 10

#define DATAFILE     "_datafile.dat"
#define NOISEFILE    "_noises.dat"
#define NOISYDATA    "_noisydata.dat"

#define PYTHON  "C:/Users/sarka/Home/Programs/college/networking/Scripts/python.exe"
#define PLOTTER "C:/Users/sarka/Home/Programs/college/networking/src/plotter/main.py"

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
    int ch, nbits = 0;
    while (is_hex(ch = getc(hexfile))) {
        write_data(datafile, ch);
        nbits += 4;
    }
    fclose(datafile);
    fclose(hexfile);

    // noise addition
    if (!(datafile = fopen(DATAFILE, "r"))) {
        printf("Failed to read %s.\n", DATAFILE);
        return 3;
    }
    FILE *noisefile;
    if (!(noisefile = fopen(NOISEFILE, "r"))) {
        printf("Failed to read %s.\n", NOISEFILE);
        return 4;
    }
    FILE *noisydata;
    if (!(noisydata = fopen(NOISYDATA, "w"))) {
        printf("Failed to write %s.\n", NOISYDATA);
        return 5;
    }
    write_noisydata(noisydata, datafile, noisefile, NUM_SAMPLES_PER_BIT, nbits);
    fclose(noisydata);
    fclose(noisefile);
    fclose(datafile);

    printf("%s %s -d %s -n %d ", PYTHON, PLOTTER, NOISYDATA, nbits);
    printf("-t \"NRZ-L\" -x \"Bit duration\" -y \"Signal\" -f \"_graph.svg\"\n");

    // decoding
    // if (!(noisydata = fopen(NOISYDATA, "r"))) {
    //     printf("Failed to read %s.\n", NOISYDATA);
    //     return 6;
    // }
    // fclose(noisydata);
    return 0;
}
