// C
#include <string.h>

// External
#include "unity.h"
#include "unity_fixture.h"

// Internal
#include "config.h"

TEST_GROUP(config);

TEST_SETUP(config) {}

TEST_TEAR_DOWN(config) {}

TEST(config, ParseConfig)
{
	struct config config;

	char data1[] = "api_key=D43E6BF6547826753356E3CAE933033FAE02F940E0638305637BE0DE5ACE9026\n"
				  "box_id=350BB118888075D7D34908DE\n"
				  "temperature_id=89A9477FBECC7D3E894C27B4\n"
				  "humidity_id=5857D8ED75AF6E617B1BD921\r\n"
				  "pressure_id=17BC7799401277B39B32BF39";

	TEST_ASSERT(config_parse(data1, strlen(data1), &config) == 0);

	char data2[] = "api_key=D43E6BF6547826753356E3CAE933033FAE02F940E0638305637BE0DE5ACE9026D43E6BF6547826753356E3CAE933033FAE02F940E0638305637BE0DE5ACE9026\n";

	TEST_ASSERT(config_parse(data2, strlen(data2), &config) == 1);

	char data3[] = "";

	TEST_ASSERT(config_parse(data3, strlen(data3), &config) == 1);
}
