#include "connection.h"

// C
#include <errno.h>
#include <stdlib.h>
#include <string.h>

// Internal
#include <tools.h>

static const size_t kAuthHeaderSize = 16 + API_KEY_SIZE + 1;
static const char kBaseUrl[] = "https://ingress.opensensemap.org/boxes/";

int32_t connection_init(CURL** _curl)
{
	errno = 0;

	if (curl_global_init(CURL_GLOBAL_ALL) != 0) {
		fprintf(stderr, "curl_global_init failed (%s)\r\n", strerror(errno));
		return 1;
	}

	*_curl = curl_easy_init();

	errno = 0;

	if (*_curl == NULL) {
		fprintf(stderr, "curl_easy_init failed (%s)\r\n", strerror(errno));
		return 1;
	}

	return 0;
}

void connection_cleanup(CURL** _curl)
{
	curl_easy_cleanup(*_curl);
	*_curl = NULL;
	curl_global_cleanup();
}

int32_t connection_initHeaders(struct curl_slist** _headers, const char* _api_key)
{
	if (*_headers != NULL) {
		curl_slist_free_all(*_headers);
	}

	char auth[kAuthHeaderSize];
	memset(auth, 0, kAuthHeaderSize);

	tools_appendString(auth, "Authorization:", kAuthHeaderSize);
	tools_appendString(auth, _api_key, kAuthHeaderSize);

	*_headers = curl_slist_append(*_headers, auth);
	*_headers = curl_slist_append(*_headers, "Content-Type: application/json");

	return 0;
}

void connection_cleanupHeaders(struct curl_slist** _headers)
{
	if (*_headers != NULL) {
		curl_slist_free_all(*_headers);
	}

	*_headers = NULL;
}

int32_t connection_prepare(const struct config* _config, const struct measurements* _measurements, const size_t _sensor,
						   struct data* _data)
{
	memset(_data->url_, 0, URL_SIZE);
	memset(_data->body_, 0, BODY_SIZE);

	tools_appendString(_data->url_, kBaseUrl, URL_SIZE);
	tools_appendString(_data->url_, _config->box_id_, URL_SIZE);
	tools_appendString(_data->url_, "/", URL_SIZE);

	char value[20];
	memset(value, 0, 20);

	switch (_sensor) {
		case kSensorTemperature: {
			tools_appendString(_data->url_, _config->temperature_id_, URL_SIZE);
			snprintf(value, 20, "%0.2f", _measurements->temperature_);
			break;
		}

		case kSensorHumidity: {
			tools_appendString(_data->url_, _config->humidity_id_, URL_SIZE);
			snprintf(value, 20, "%0.2f", _measurements->humidity_);
			break;
		}

		case kSensorPressure: {
			tools_appendString(_data->url_, _config->pressure_id_, URL_SIZE);
			snprintf(value, 20, "%0.2f", _measurements->pressure_);
			break;
		}

		default: {
			fprintf(stderr, "Unknown sensor\r\n");
			return 1;
		}
	}

	tools_appendString(_data->body_, "{\"value\":", BODY_SIZE);
	tools_appendString(_data->body_, value, BODY_SIZE);
	tools_appendString(_data->body_, "}", BODY_SIZE);

	printf("URL: %s\r\n", _data->url_);
	printf("Body: %s\r\n", _data->body_);

	return 0;
}

int32_t connection_send(CURL** _curl, const struct curl_slist** _headers, const struct data* _data)
{
	int32_t return_value = 0;

	struct response response;

	CURLcode result;

	response.size_ = 0;
	response.data_ = NULL;

	if (*_curl) {
		curl_easy_setopt(*_curl, CURLOPT_URL, _data->url_);
		curl_easy_setopt(*_curl, CURLOPT_HTTPHEADER, *_headers);
		curl_easy_setopt(*_curl, CURLOPT_POSTFIELDSIZE, -1L);
		curl_easy_setopt(*_curl, CURLOPT_POSTFIELDS, _data->body_);
		curl_easy_setopt(*_curl, CURLOPT_WRITEFUNCTION, tools_appendData);
		curl_easy_setopt(*_curl, CURLOPT_WRITEDATA, (void*)&response);
		curl_easy_setopt(*_curl, CURLOPT_VERBOSE, 0L);

		result = curl_easy_perform(*_curl);

		printf("> %s\r\n", response.data_);

		if (response.data_ != NULL) {
			free(response.data_);
		}

		if (result != CURLE_OK) {
			fprintf(stderr, "curl_easy_perform() failed: %s\r\n", curl_easy_strerror(result));
			return_value = 1;
		}
	}

	return return_value;
}
