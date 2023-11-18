#include "noise_addition.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <stdlib.h>

char *gray_to_bin(char *graycode, char *binary)
{
    int i = 0;
    binary[0] = graycode[0];
    for (i = 1; graycode[i]; ++i) 
        binary[i] = INT_TO_CHAR(CHAR_TO_INT(graycode[i-1]) ^ CHAR_TO_INT(graycode[i]));
    binary[i] = '\0';
    return binary;
}

int bin_to_int(char *binary)
{
    int value = 0;
    for (int i = 0; binary[i]; ++i) 
        value = 2 * value + CHAR_TO_INT(binary[i]);
    return value;
}

void write_noisy_data(FILE *noisydata, FILE *datafile, FILE *noisefile, int nbits, int nsymbols, int nsamples)
{
    int index, symbol, time_int = 0;
    char *binary = calloc(nbits+1, sizeof(char));
    char *graycode = calloc(nbits+1, sizeof(char));
    double ac, as, phase;
    double signal, time, noise = 0.0;
    for (int i = 0; i < nsymbols; ++i) {
        fscanf(datafile, "%d", &index);
        fscanf(datafile, "%s", graycode);
        symbol = bin_to_int(gray_to_bin(graycode, binary));
        phase = (1+2*symbol) * M_PI / pow(2, nbits);
        for (int j = 0; j < nsamples; ++j) {
            ac = AMPLITUDE * cos(phase);
            as = -AMPLITUDE * sin(phase);
            fprintf(noisydata, "%lf ", index+(double)j/nsamples);
            time = time_int + (double)j/nsamples;
            fscanf(noisefile, "%lf", &noise);
            fprintf(noisydata, "%lf ", ac*cos(2*M_PI*FREQUENCY*time)+as*sin(2*M_PI*FREQUENCY*time)+noise);
        }
        ++time_int;
    }
    free(graycode);
    free(binary);
}
