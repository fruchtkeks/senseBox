// C
#include <string.h>

// External
#include "unity.h"
#include "unity_fixture.h"

// Internal
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