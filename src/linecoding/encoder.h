#ifndef ENCODER_H
#define ENCODER_H

#include <stdio.h>

static inline int is_hex(int ch)
{
    return ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f'));
}

/**
 * @param ch
 * Hex character to be converted into binary.
 * @return
 * Returns the binary equivalent as a c-string.
 * If ch is not any valid hex character, returns "0000".
*/
char *hex_to_bin(int ch);

/**
 * @param datafile
 * Stream where the signal is written into.
 * @param ch
 * Hexadecimal character whose signal has to be written.
 * @param index
 * Time of the signal of the first bit.
 * @note
 * datafile must be writable.
 * ch must be a hex character.
*/
void write_data(FILE *datafile, int ch);

#endif