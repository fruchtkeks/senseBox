#ifndef SENSEBOX_CONNECTION_H
#define SENSEBOX_CONNECTION_H

// C
#include <stdint.h>

// External
#include <curl/curl.h>

// Internal
#include "common.h"

void connection_init(CURL** _curl);

void connection_cleanup(CURL** _curl);

int32_t connection_send(CURL** _curl, const struct config* _config, const struct data* _data);

#endif
