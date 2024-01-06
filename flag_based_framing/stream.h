#ifndef STREAM_H
#define STREAM_H

#include <stdbool.h>

#define FILE_STREAM_SIZE    16
#define STREAM_GROW_SIZE    4

typedef struct Stream {
    int size, length;
    char *buffer;
} Stream;

Stream *create_empty_stream(int size);
Stream *stream_from_file(const char *filename);
void delete_stream(Stream *stream);

bool append_char(Stream *stream, char ch);
bool append_str(Stream *stream, const char *s);

/**
 * @note
 * Appends char at end, but the stream does not
 * increase in size.
 * If stream buffer is full, removes the first
 * char.
*/
bool append_char_nogrow(Stream *stream, char ch);

bool stream_endswith(const Stream *stream, const char *s);
bool stream_equal(const Stream *stream, const char *s);

/**
 * @note
 * Strips n characters from the end of stream.
 * Simply sets length to length-4.
*/
void stream_rstripn(Stream *stream, int n);

/**
 * @note
 * Newline added after stream.
*/
void print_stream(const Stream *stream);

#endif
