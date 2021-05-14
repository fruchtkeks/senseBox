#ifndef SENSEBOX_CONNECTION_H
#define SENSEBOX_CONNECTION_H

// C
#include <stdint.h>

// External
#include <curl/curl.h>

// Internal
#include "common.h"

/**
 * Initializes the cURL handler.
 *
 * @param _curl A pointer to the cURL handler.
 *
 * @return Returns 0 on success and 1 on any error.
 */
int32_t connection_init(CURL** _curl);

/**
 * Performs a cleanup of the cURL handler.
 *
 * @param _curl The pointer to the cURL handler.
 *
 * @return Returns 0 on success and 1 on any error.
 */
int32_t connection_cleanup(CURL** _curl);

/**
 * Sends the data from the data structure to the openSenseMap API.
 *
 * @param _curl A pointer to the cURL handler.
 * @param _config A pointer to the config structure.
 * @param _data A pointer to the data structure with the current measurements.
 *
 * @return Return 0 on success and 1 on any error.
 */
int32_t connection_send(CURL** _curl, const struct config* _config, const struct data* _data);

#endif
