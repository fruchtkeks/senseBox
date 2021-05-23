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
 */
void connection_cleanup(CURL** _curl);

/**
 * Init. the cURL header structure.
 *
 * @param _headers The cURL header structure.
 * @param _api_key The key for the openSenseMap API.
 *
 * @return Returns 0 on success and 1 on any error.
 */
int32_t connection_initHeaders(struct curl_slist** _headers, const char* _api_key);

/**
 * Cleans up the cURL header structure.
 *
 * @param _headers The cURL header structure.
 */
void connection_cleanupHeaders(struct curl_slist** _headers);

/**
 * Prepares the sensor measurements for the request to the openSenseMap API.
 *
 * @param _config A pointer to the config structure.
 * @param _measurements A pointer to the data structure with the current measurements.
 * @param _sensor The sensor type for the request (e.g. temperature, humidity, etc.).
 * @param[out] _data A pointer to the data structure that holds the requests URL and body.
 *
 * @return Returns 0 on success and 1 on any error.
 */
int32_t connection_prepare(const struct config* _config, const struct measurements* _measurements, size_t _sensor,
						   struct data* _data);

/**
 * Performs the request to the openSenseMap API.
 *
 * @param _curl A pointer to the cURL handler.
 * @param _headers The cURL header structure.
 * @param _data A pointer to the data structure that holds the request data.
 *
 * @return Returns 0 on success and 1 on any error.
 */
int32_t connection_send(CURL** _curl, const struct curl_slist** _headers, const struct data* _data);

#endif
