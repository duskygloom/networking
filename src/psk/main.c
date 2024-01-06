#include "encoder.h"
#include "noise_addition.h"

#include <stdlib.h>

#define DATAFILE    "_datafile.txt"
#define NOISEFILE   "_noises.txt"
#define NOISYDATA   "_noisydata.txt"
#define BINARYFILE  "_binary.txt"

#define NPSK        8

#define PYTHON  "python3"
#define PLOTTER "../plotter/main.py"

#define NUM_SAMPLES_PER_BIT 100

int main(int argc, char **argv) {
    // hex to binary
    FILE *hexfile, *binfile;
    if (argc < 2) {
        puts("Missing required argument: hex file");
        return 1;
    }
    else if (!(hexfile = fopen(argv[1], "r"))) {
        printf("Failed to read: %s\n", argv[1]);
        return 1;
    }
    else if (!(binfile = fopen(BINARYFILE, "w"))) {
        printf("Failed to write: %s\n", BINARYFILE);
        return 1;
    }
    int nbin = write_binary_data(binfile, hexfile);
    fclose(binfile);
    fclose(hexfile);
    // preprocess and prepend zeroes
    // series to parallel: read multiple bits at once
    FILE *datafile;
    if (!(binfile = fopen(BINARYFILE, "r"))) {
        printf("Failed to read: %s\n", BINARYFILE);
        return 1;
    }
    if (!(datafile = fopen(DATAFILE, "w"))) {
        printf("Failed to write: %s\n", DATAFILE);
        return 1;
    }
    int nsymbols = write_data(datafile, binfile, nbin, NPSK);
    fclose(datafile);
    fclose(binfile);
    // derive ac and as: based on the multiple bits
    // ac * cos2pift, as * sin2pift
    // ac * cos2pift + as * sin2pift = S
    FILE *noisydata, *noisefile;
    if (!(noisydata = fopen(NOISYDATA, "w"))) {
        printf("Failed to write: %s\n", NOISYDATA);
        return 1;
    }
    if (!(datafile = fopen(DATAFILE, "r"))) {
        printf("Failed to read: %s\n", DATAFILE);
        return 1;
    }
    if (!(noisefile = fopen(NOISEFILE, "r"))) {
        printf("Failed to read: %s\n", NOISEFILE);
        return 1;
    }
    write_noisy_data(noisydata, datafile, noisefile, NPSK, nsymbols, NUM_SAMPLES_PER_BIT);
    fclose(noisefile);
    fclose(datafile);
    fclose(noisydata);
    // printing plotting command
    char command[200];
    sprintf(command, "%s %s -d %s -n %d -t \"%d-PSK\" -x \"Bit duration\" -y \"Signal\" -s 0.1 -f \"_graph.svg\"\n", 
            PYTHON, PLOTTER, NOISYDATA, nsymbols, NPSK);
    puts(command);
    system(command);
    return 0;
}
