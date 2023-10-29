#include "noise_addition.h"

#include <stdio.h>

void write_noisydata(FILE *noisydata, FILE *data, FILE *noises, int samples_per_bit, int nbits)
{
    int index;
    float signal, noise;
    for (int i = 0; i < nbits; ++i) {
        fscanf(data, "%d %f", &index, &signal);
        for (int sample = 0; sample < samples_per_bit; ++sample) {
            fscanf(noises, "%f", &noise);
            fprintf(noisydata, "%.4f %.4f ", (float)sample/samples_per_bit+index, signal+noise);
        }
    }
}
