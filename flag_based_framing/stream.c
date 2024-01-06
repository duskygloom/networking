#include "stream.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Stream *create_empty_stream(int size)
{
    Stream *stream = malloc(sizeof(Stream));
    if (!stream) return NULL;
    stream->size = size;
    stream->length = 0;
    stream->buffer = calloc(size, sizeof(char));
    if (!stream->buffer) {
        free(stream);
        return NULL;
    }
    return stream;
}

Stream *stream_from_file(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (!fp) return NULL;
    Stream *stream = create_empty_stream(FILE_STREAM_SIZE);
    char ch = fgetc(fp);
    while (ch == '0' || ch == '1') {
        append_char(stream, ch);
        ch = fgetc(fp);
    }
    fclose(fp);
    return stream;
}

void delete_stream(Stream *stream)
{
    if (stream) {
        if (stream->buffer) free(stream->buffer);
        stream->size = stream->length = 0;
        free(stream);
    }
}

bool append_char(Stream *stream, char ch)
{
    if (stream->size < stream->length+1) {
        char *re = realloc(stream->buffer, stream->size+STREAM_GROW_SIZE);
        if (!re) {
            printf("Realloc failed: %d\n", stream->size);
            return false;
        }
        stream->buffer = re;
        stream->size += STREAM_GROW_SIZE;
    }
    stream->buffer[stream->length++] = ch;
    return true;
}

bool append_str(Stream *stream, const char *s)
{
    int length = strlen(s);
    int ngrows = length/STREAM_GROW_SIZE+1;
    if (stream->size < stream->length+length) {
        char *re = realloc(stream->buffer, stream->size+ngrows*STREAM_GROW_SIZE);
        if (!re) {
            printf("Realloc failed: %d\n", stream->size);
            return false;
        }
        stream->buffer = re;
        stream->size += ngrows*STREAM_GROW_SIZE;
    }
    while (*s) stream->buffer[stream->length++] = *s++;
    return true;
}

bool append_char_nogrow(Stream *stream, char ch)
{
    if (stream->size < stream->length+1) {
        if (!memmove(stream->buffer, stream->buffer+1, stream->size-1))
            return false;
        --stream->length;
    }
    stream->buffer[stream->length++] = ch;
    return true;
}

bool stream_endswith(const Stream *stream, const char *s)
{
    int length = strlen(s);
    int index = stream->length-length;
    if (index < 0) return false;
    while (index < stream->length && stream->buffer[index++] == *s++);
    return index == stream->length;
}

bool stream_equal(const Stream *stream, const char *s)
{
    int length = strlen(s);
    if (length != stream->length) return false;
    int index = 0;
    while (index < stream->length && stream->buffer[index++] == *s++);
    return index == stream->length;
}

void stream_rstripn(Stream *stream, int n)
{
    stream->length -= n;
    stream->length = stream->length < 0 ? 0 : stream->length;
}

void print_stream(const Stream *stream)
{
    for (int i = 0; i < stream->length; ++i)
        putchar(stream->buffer[i]);
    putchar('\n');
}
