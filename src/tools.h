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

#endif
