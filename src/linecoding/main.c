#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define DATAFILE    "datafile.txt"

#define NUM_SAMPLES_PER_BIT 10
// #define NOISELESS

#define PYTHON  "python3"
#define PLOTTER "../plotter/main.py"

void hex_to_bin(char ch, int *buffer)
{
    switch (ch) {
        case '0':
            buffer[0] = 0;
            buffer[1] = 0;
            buffer[2] = 0;
            buffer[3] = 0;
            break;
        case '1':
            buffer[0] = 0;
            buffer[1] = 0;
            buffer[2] = 0;
            buffer[3] = 1;
            break;
        case '2':
            buffer[0] = 0;
            buffer[1] = 0;
            buffer[2] = 1;
            buffer[3] = 0;
            break;
        case '3':
            buffer[0] = 0;
            buffer[1] = 0;
            buffer[2] = 1;
            buffer[3] = 1;
            break;
        case '4':
            buffer[0] = 0;
            buffer[1] = 1;
            buffer[2] = 0;
            buffer[3] = 0;
            break;
        case '5':
            buffer[0] = 0;
            buffer[1] = 1;
            buffer[2] = 0;
            buffer[3] = 1;
            break;
        case '6':
            buffer[0] = 0;
            buffer[1] = 1;
            buffer[2] = 1;
            buffer[3] = 0;
            break;
        case '7':
            buffer[0] = 0;
            buffer[1] = 1;
            buffer[2] = 1;
            buffer[3] = 1;
            break;
        case '8':
            buffer[0] = 1;
            buffer[1] = 0;
            buffer[2] = 0;
            buffer[3] = 0;
            break;
        case '9':
            buffer[0] = 1;
            buffer[1] = 0;
            buffer[2] = 0;
            buffer[3] = 1;
            break;
        case 'a':
        case 'A':
            buffer[0] = 1;
            buffer[1] = 0;
            buffer[2] = 1;
            buffer[3] = 0;
            break;
        case 'b':
        case 'B':
            buffer[0] = 1;
            buffer[1] = 0;
            buffer[2] = 1;
            buffer[3] = 1;
            break;
        case 'c':
        case 'C':
            buffer[0] = 1;
            buffer[1] = 1;
            buffer[2] = 0;
            buffer[3] = 0;
            break;
        case 'd':
        case 'D':
            buffer[0] = 1;
            buffer[1] = 1;
            buffer[2] = 0;
            buffer[3] = 1;
            break;
        case 'e':
        case 'E':
            buffer[0] = 1;
            buffer[1] = 1;
            buffer[2] = 1;
            buffer[3] = 0;
            break;
        case 'f':
        case 'F':
            buffer[0] = 1;
            buffer[1] = 1;
            buffer[2] = 1;
            buffer[3] = 1;
            break;
    }
}

char bin_to_hex(const int *buffer)
{
    char ch = 0;
    for (int i = 0; i < 4; ++i)
        ch = 2*ch + buffer[i];
    if (ch < 10) return ch + '0';
    else return ch + 'A' - 10;
}

/**
 * @return
 * Returns a random double from [lower, upper).
*/
double uniform(double lower, double upper)
{
    double range = upper-lower;
    int int_form = (int)(10000*range);
    return lower + (rand() % int_form) / 10000.0;
}

int main(int argc, char **argv)
{
    FILE *datafile, *srcfile;
    if ((datafile = fopen(DATAFILE, "w")) == NULL) {
        printf("[Abort] Could not write: %s\n", DATAFILE);
        return 0;
    }

    printf("\nEncoding.\n");
    
    if (argc <= 1 || (srcfile = fopen(argv[1], "r")) == NULL) {
        printf("Hexadecimal: ");
        srcfile = stdin;
    }    

    char ch;
    int base = 0, nbits = 0, buffer[4] = {0};
    double time, signal, noise, avg_signal;
    while (isxdigit(ch = getc(srcfile))) {
        hex_to_bin(ch, buffer);
        nbits += 4;
        for (int i = 0; i < 4; ++i, ++base)
            for (int j = 0; j < NUM_SAMPLES_PER_BIT; ++j) {
                time = base + j/(double)NUM_SAMPLES_PER_BIT;
                signal = 2*buffer[i]-1;
                #ifdef NOISELESS
                noise = 0;
                #else
                noise = uniform(-0.5, 0.5);
                #endif
                fprintf(datafile, "%.2lf %.2lf ", time, signal+noise);
            }
    }

    fclose(srcfile);
    fclose(datafile);

    printf("\nDecoding.\n");

    if ((datafile = fopen(DATAFILE, "r")) == NULL) {
        printf("[Abort] Could not read: %s\n", DATAFILE);
        return 0;
    }

    base = 0;
    for (int k = 0; k < nbits/4; ++k) {
        for (int i = 0; i < 4; ++i, ++base) {
            avg_signal = 0.0;
            for (int j = 0; j < NUM_SAMPLES_PER_BIT; ++j) {
                fscanf(datafile, "%lf %lf", &time, &signal);
                avg_signal += signal;
            }
            avg_signal /= NUM_SAMPLES_PER_BIT;
            buffer[i] = (signal > 0);
        }
        putchar(bin_to_hex(buffer));
    }
    putchar('\n');

    fclose(datafile);

    printf("%s %s -d %s -n %d ", PYTHON, PLOTTER, DATAFILE, nbits);
    printf("-t \"NRZ-L\" -x \"Bit duration\" -y \"Signal\" -f \"_graph.svg\"\n");

    return 0;
}
