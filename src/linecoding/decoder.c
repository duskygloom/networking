#include "decoder.h"

char bin_to_hex(char *bin)
{
    int value = 0;
    // while (*bin)                                            // bin to dec
    //     value = 2 * value +  (*bin++ - '0');
    // could use loop but its simpler and faster in this case
    value += 8 * bin[0];
    value += 4 * bin[1];
    value += 2 * bin[2];
    value += 1 * bin[3];
    if (value > 9) return value - 9 + 'A';                  // alphabets if greater than 9
    return value + '0';                                     // else digits
}
