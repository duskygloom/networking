#include "stream.h"

#define FLAG		"011110"
#define FLAG_STRIP	"0111"
#define FLAG_LENGTH	6

#include <stdio.h>

Stream *tx(const Stream *stream, Stream *change);
Stream *rx(const Stream *stream);

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("Missing bitstream file.\n");
		printf("Usage: %s <file>\n", argv[0]);
		return 0;
	}
	Stream *stream = stream_from_file(argv[1]);
	printf("Original stream		: ");
	print_stream(stream);
	Stream *change = create_empty_stream(stream->size);
	Stream *txstream = tx(stream, change);
	delete_stream(stream);
	printf("Transmitted stream	: ");
	print_stream(txstream);
	printf("Bit stuffing		: ");
	print_stream(change);
	Stream *rxstream = rx(txstream);
	delete_stream(txstream);
	printf("Received stream		: ");
	print_stream(rxstream);
	delete_stream(rxstream);
	return 0;
}

Stream *tx(const Stream *stream, Stream *change)
{
	Stream *txstream = create_empty_stream(stream->length);
	for (int i = 0; i < stream->length; ++i) {
		if (stream_endswith(txstream, FLAG_STRIP)) {
			append_char(change, '^');
			append_char(txstream, '0');
		}
		append_char(change, ' ');
		append_char(txstream, stream->buffer[i]);
	}
	for (int i = 0; i < FLAG_LENGTH; ++i)
		append_char(change, '-');
	append_str(txstream, FLAG);
	return txstream;
}

Stream *rx(const Stream *stream)
{
	Stream *rxstream = create_empty_stream(stream->length);
	Stream *buffer = create_empty_stream(FLAG_LENGTH-2);
	for (int i = 0; i < stream->length; ++i) {
		char bit = stream->buffer[i];
		bool found_0111 = stream_equal(buffer, FLAG_STRIP);
		if (found_0111 && bit == '0')
			append_char_nogrow(buffer, bit);
		else if (found_0111) {
			stream_rstripn(rxstream, FLAG_LENGTH-2);
			break;
		}
		else {
			append_char_nogrow(buffer, bit);
			append_char(rxstream, bit);
		}
	}
	delete_stream(buffer);
	return rxstream;
}
