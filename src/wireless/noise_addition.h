#ifndef NOISE_ADDITION_H
#define NOISE_ADDITION_H

#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

#define AMPLITUDE       1.0
#define FREQUENCY       10.0
#define PHASEDIFF       0.0

#define SIGNAL_AT(time) (AMPLITUDE * cos(2*M_PI*FREQUENCY*time + PHASEDIFF))
#define SIGNAL_AT_PHASE(time, phase) (AMPLITUDE * cos(2*M_PI*FREQUENCY*time + phase))

/**
 * @param noisydata
 * stream where the noisy data will be written
 * must be writable
 * @param data
 * stream from where the original data will be read
 * must be readable
 * @param noise
 * stream from where noise values will be read
 * must be readable
 * @param samples_per_bit
 * number of samples in a bit duration
 * @param nbits
 * number of bits in the stream
*/
void write_noisydata(FILE *noisydata, FILE *data, FILE *noise, int samples_per_bit, int nbits);

#endif
