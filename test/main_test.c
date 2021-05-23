// External
#include "unity_fixture.h"

TEST_GROUP_RUNNER(config) { RUN_TEST_CASE(config, ParseConfig); }

TEST_GROUP_RUNNER(tools) { RUN_TEST_CASE(tools, Append); }

static void run_tests(void)
{
	RUN_TEST_GROUP(config);
	RUN_TEST_GROUP(tools);
}

int main(int argc, const char* argv[]) { return UnityMain(argc, argv, run_tests); }
