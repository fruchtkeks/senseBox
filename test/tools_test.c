// C
#include <string.h>

// External
#include "unity.h"
#include "unity_fixture.h"

// Internal
#include "common.h"
#include "tools.h"

TEST_GROUP(tools);

TEST_SETUP(tools) {}

TEST_TEAR_DOWN(tools) {}

TEST(tools, AppendString)
{
	char buffer[10];
	memset(buffer, 0, 10);

	TEST_ASSERT(tools_appendString(buffer, "abcde", 10) == 0);
	TEST_ASSERT(strlen(buffer) == 5);
	TEST_ASSERT(tools_appendString(buffer, "fghi", 10) == 0);
	TEST_ASSERT(strlen(buffer) == 9);
	TEST_ASSERT(tools_appendString(buffer, "j", 10) == 1);
	TEST_ASSERT(strlen(buffer) == 9);
}

TEST(tools, AppendData)
{
	struct response response;

	response.size_ = 0;
	response.data_ = NULL;

	const char* data = "abcde";

	TEST_ASSERT(tools_appendData((void*)data, 5, 1, (void*)&response) == 5);
	TEST_ASSERT(response.size_ == 5);
}