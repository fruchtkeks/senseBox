#ifndef SENSEBOX_CONFIG_H
#define SENSEBOX_CONFIG_H

// C
#include <stddef.h>
#include <stdint.h>

// Internal
#include "common.h"

/**
 * Reads the data from the file located at fullpath, tries to parse the data,
 * and fills the config structure.
 *
 * @param _fullpath The path to the configuration file (e.g. /opt/senseBox/box.config).
 * @param _config A pointer to the config structure, that contains the config after parsing.
 *
 * @return Returns 0 on success and 1 on any error.
 */
int32_t config_parseFromFile(const char* _fullpath, struct config* _config);

/**
 * Parses the config from the buffer and fills the config structure.
 *
 * @param _data The buffer, that contains the raw config data (e.g. read from file).
 * @param _data_size The size of the buffer with the raw config.
 * @param _config A pointer to the config structure, that is filled with the parsed values from the buffer.
 *
 * @return Returns 0 on success and 1 on any error.
 */
int32_t config_parse(char* _data, size_t _data_size, struct config* _config);

#endif
