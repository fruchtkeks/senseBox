#include "tools.h"

// C
#include <errno.h>
#include <stdio.h>

int32_t tools_append(char* _destination, const char* _source, size_t _destination_size)
{
	size_t destination_length = strlen(_destination);
	size_t source_length = strlen(_source);

	if (destination_length + source_length + 1 > _destination_size) {
		fprintf(stderr, "Not enough free space in the destination string\r\n");
		return 1;
	}

	errno = 0;

	strncat(_destination, _source, _destination_size);

	if (errno != 0) {
		fprintf(stderr, "Error while appending the string to the destination (%s)\r\n", strerror(errno));
		return 1;
	}

	return 0;
}