#ifndef BIT_BUFFER_C
#define BIT_BUFFER_C

#include <stdlib.h>
#include <string.h>

extern int FLAG_LENGTH;

typedef struct BitBuffer {
	char buffer[FLAG_LENGTH];
	int cursor;
} BitBuffer;

BitBuffer *create_bitbuffer()
{
	BitBuffer *buffer = malloc(sizeof(BitBuffer));
	buffer->cursor = 0;
	return buffer;
}

void delete_buffer(BitBuffer *buffer)
{
	free(buffer);
}

bool compare_buffer(const BitBuffer *buffer, const char *comparision)
{
	int check = 0;
	while (check < FLAG_LENGTH && comparision[check]);
	return check == FLAG_LENGTH;
}

int insert_bit(BitBuffer *buffer, char bit)
{
	if ()	
}

#endif

