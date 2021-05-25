#include "tools.h"

// C
#include <stdio.h>

int32_t tools_append(char* _destination, const char* _source, size_t _destination_size)
{
	size_t destination_length = strlen(_destination);
	size_t source_length = strlen(_source);

	if (destination_length + source_length + 1 > _destination_size) {
		fprintf(stderr, "Not enough free space in the destination string\r\n");
		return 1;
	}

	strncat(_destination, _source, _destination_size);

	return 0;
}