#include "connection.h"

// C
#include <errno.h>
#include <stdlib.h>
#include <string.h>

struct memory {
	char* response_;
	size_t size_;
};

static size_t receive(void* _data, size_t _size, size_t _nmemb, char* _received_data)
{
	size_t real_size = _size * _nmemb;
	struct memory* mem = (struct memory*)_received_data;

	if (mem->size_ == 0) {
		mem->response_ = malloc(real_size + 1);
	} else {
		char* ptr = realloc(mem->response_, mem->size_ + real_size + 1);

		if (!ptr) {
			return 0;
		}

		mem->response_ = ptr;
	}

	memcpy(&(mem->response_[mem->size_]), _data, real_size);
	mem->size_ += real_size;
	mem->response_[mem->size_] = 0;

	return real_size;
}

//

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
	curl_global_cleanup();
}

int32_t connection_send(CURL** _curl, const struct config* _config, const struct data* _data)
{
	CURLcode result;

	if (*_curl) {
		char auth[500];
		memset(auth, 0, 500);

		strcat(auth, "Authorization:");
		strcat(auth, _config->api_key_);

		struct curl_slist* headers = NULL;

		headers = curl_slist_append(headers, auth);
		headers = curl_slist_append(headers, "Content-Type: application/json");

		curl_easy_setopt(*_curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(*_curl, CURLOPT_POSTFIELDSIZE, -1L);
		curl_easy_setopt(*_curl, CURLOPT_WRITEFUNCTION, receive);
		curl_easy_setopt(*_curl, CURLOPT_VERBOSE, 0L);

		for (size_t sensor = 0; sensor < kSensorSize; ++sensor) {
			struct memory received_data;

			received_data.response_ = NULL;
			received_data.size_ = 0;

			char url[500];
			memset(url, 0, 500);

			strcat(url, "https://ingress.opensensemap.org/boxes/");
			strcat(url, _config->box_id_);
			strcat(url, "/");

			char value[100];
			memset(value, 0, 100);

			switch (sensor) {
				case kSensorTemperature: {
					strcat(url, _config->temperature_id_);
					sprintf(value, "%0.2f", _data->temperature_);
					break;
				}

				case kSensorHumidity: {
					strcat(url, _config->humidity_id_);
					sprintf(value, "%0.2f", _data->humidity_);
					break;
				}

				case kSensorPressure: {
					strcat(url, _config->pressure_id_);
					sprintf(value, "%0.2f", _data->pressure_);
					break;
				}

				default: {
					fprintf(stderr, "Unknown sensor\r\n");
				}
			}

			char body[500];
			memset(body, 0, 500);

			strcat(body, "{\"value\":");
			strcat(body, value);
			strcat(body, "}");

			printf("Body: %s\r\n", body);

			curl_easy_setopt(*_curl, CURLOPT_URL, url);
			curl_easy_setopt(*_curl, CURLOPT_POSTFIELDS, body);
			curl_easy_setopt(*_curl, CURLOPT_WRITEDATA, (void*)&received_data);

			result = curl_easy_perform(*_curl);

			printf("> %s\r\n", received_data.response_);

			if (received_data.response_ != NULL) {
				free(received_data.response_);
			}

			if (result != CURLE_OK) {
				fprintf(stderr, "curl_easy_perform() failed: %s\r\n", curl_easy_strerror(result));
				break;
			}
		}

		curl_slist_free_all(headers);
	}

	return 0;
}