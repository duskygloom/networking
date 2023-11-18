#ifndef NOISE_ADDITION_H
#define NOISE_ADDITION_H

#include <stdio.h>

#define AMPLITUDE 1
#define FREQUENCY 10
#define SIGNAL_AT_AMP(time, amp) amp * cos(2*M_PI*FREQUENCY*time)

#define CHAR_TO_INT(ch) ch - '0'
#define INT_TO_CHAR(n)  n + '0'

/**
 * @note
 * strlen(binary) >= strlen(graycode)
 * @returns
 * binary and thus binary can be chained with other functions
*/
char *gray_to_bin(char *graycode, char *binary);

int bin_to_int(char *binary);

/**
 * @param noisydata
 * file stream where noisy data will be written
 * this is the final data on which will be passed to the plotter
 * @param datafile
 * file stream where intermediate symbols are stored
 * @param noisefile
 * file stream where noise values are stored
 * @param nbits
 * number of bits read together
 * used to convert from symbols to phi values
 * @param nsymbols
 * number of symbols in datafile
 * @param nsamples
 * number of samples per bit duration
 * @note
 * datafile should be properly generated and the symbols in it should be nbits long
*/
void write_noisy_data(FILE *noisydata, FILE *datafile, FILE *noisefile, int nbits, int nymbols, int nsamples);

#endif
