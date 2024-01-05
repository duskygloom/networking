#include <stdio.h>
#include <string.h>

#define MAX_FILE_LENGTH	50
#define FLAG_LENGTH		6

static char buffer[FLAG_LENGTH-2];
static int cursor = 0;

void insert_bit(char bit)
{
	if (compare_buff("0111")) {
		buffer[0] = '0';
		buffer[1] = bit;
		cursor = 2;
		return;
	}
	if (cursor < FLAG_LENGTH-2) {
		buffer[cursor] = bit;
		return;
	}
	memmove(buffer, buffer+1, FLAG_LENGTH-1);
	buffer[FLAG_LENGTH-3] = bit;
}

int compare_buff(const char *s)
{
	int check = 0;
	while (check < FLAG_LENGTH && 
			s[check] == buffer[check]);
	return check == FLAG_LENGTH;								// loop completed
}

int main(int argc, char **argv)
{
	// checking arguments
	if (argc < 2) {
		printf("Missing arguments.\n");
		printf("Usage: %s <bitstream>\n", argv[0]);
		return 1;
	}
	
	BitBuffer *buffer = create_buffer();
	FILE *bitsfile = fopen(argv[1], "r");
	if (!bitsfile) {
		printf("Could not read file: %s\n", argv[1]);
		return 1;
	}
	
	while (!feof(bitsfile)) {
		if (compare_buffer(buffer, ))	
	}

	delete_bitbuffer(buffer);
	fclose(bitsfile);

	return 0;
}

