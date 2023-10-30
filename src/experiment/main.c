#include <stdio.h>

static inline int is_hex(char ch) {
    return (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F');
}

/**
 * @note
 * returns -1 if ch is not a hex character
*/
int hex_to_int(char ch) {
    if (ch >= '0' && ch <= '9') return ch - '0';
    else if (ch >= 'A' && ch <= 'F') return ch - 'A' + 9;
    else if (ch >= 'a' && ch <= 'f') return ch - 'a' + 9;
    return -1;
}

int hexfile_to_int(FILE *hexfile) {
    int value = 0;
    char ch;
    while (is_hex(ch = getc(hexfile)))
        value = 16 * value + hex_to_int(ch);
    return value;
}

char *int_

int main(int argc, char **argv) {
    FILE *hexfile;
    if (argc < 2) {
        puts("Expecting 1 argument: hexadecimal file.");
        return 0;
    } else if (!(hexfile = fopen(argv[1], "r"))) {
        printf("Failed to read: %s\n", argv[1]);
        return 0;
    }
    printf("%d\n", hexfile_to_int(hexfile));
    fclose(hexfile);
    return 0;
}