#ifndef ENCODER_H
#define ENCODER_H

#include <stdio.h>

#define IS_BIN(ch) (ch == '0' || ch == '1')
#define IS_HEX(ch) (ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f')

char *hex_to_bin(char ch);

int write_binary_data(FILE *binfile, FILE *hexfile);

/**
 * @param datafile
 * stream where the data is written
 * @param binfile
 * stream from where binary is read
 * @param nbin
 * number of bits in binfile
 * @param nbit
 * number of bits to be read at once
 * @returns
 * number of symbols written into datafile
*/
int write_data(FILE *datafile, FILE *binfile, int nbin, int nbit);

#endif
