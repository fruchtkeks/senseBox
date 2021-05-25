#ifndef SENSEBOX_TOOLS_H
#define SENSEBOX_TOOLS_H

// C
#include <stdint.h>
#include <string.h>

/**
 * Appends the source string to the destination string.
 *
 * @param _destination The string to be extended.
 * @param _source The string to be appended.
 * @param _destination_size The max. size of the destination string.
 *
 * @return Returns 0 on success, otherwise 1.
 */
int32_t tools_appendString(char* _destination, const char* _source, size_t _destination_size);

/**
 * Appends the received data to the data buffer.
 *
 * @info (Re-) Allocates the buffer for storing the data.
 *
 * @param _input The received data, that will be stored.
 * @param _size The size of the received data.
 * @param _nmemb Received data member count.
 * @param _output The buffer, where the data is stored.
 *
 * @return The number of bytes, that have been stored in the data buffer.
 */
size_t tools_appendData(char* _input, size_t _size, size_t _nmemb, void* _output);

#endif
