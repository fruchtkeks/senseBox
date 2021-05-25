#include "tools.h"

// C
#include <stdio.h>
#include <stdlib.h>

// Internal
#include "common.h"

int32_t tools_appendString(char* _destination, const char* _source, size_t _destination_size)
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

size_t tools_appendData(char* _input, size_t _size, size_t _nmemb, void* _output)
{
	size_t real_size = _size * _nmemb;
	struct response* response = (struct response*)_output;

	if (response->size_ == 0) {
		response->data_ = malloc(real_size + 1);
	} else {
		char* ptr = realloc(response->data_, response->size_ + real_size + 1);

		if (!ptr) {
			return 0;
		}

		response->data_ = ptr;
	}

	memcpy(&(response->data_[response->size_]), _input, real_size);
	response->size_ += real_size;
	response->data_[response->size_] = 0;

	return real_size;
}