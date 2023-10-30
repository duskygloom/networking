#include "noise_addition.h"

#include <stdio.h>

void write_noisydata(FILE *noisydata, FILE *data, FILE *noises, int samples_per_bit, int nbits)
{
    int index;
    double signal, noise, time;
    for (int i = 0; i < nbits; ++i) {
        fscanf(data, "%d %lf", &index, &signal);
        for (int sample = 0; sample < samples_per_bit; ++sample) {
            time = (double)sample/samples_per_bit+index;
            fscanf(noises, "%lf", &noise);
            fprintf(noisydata, "%.4lf %.4lf ", time, SIGNAL_AT(time));
        }
    }
}
