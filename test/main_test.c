// External
#include "unity_fixture.h"

TEST_GROUP_RUNNER(config) { RUN_TEST_CASE(config, ParseConfig); }

TEST_GROUP_RUNNER(sensor)
{
	RUN_TEST_CASE(sensor, Init);
	RUN_TEST_CASE(sensor, Read);
}

TEST_GROUP_RUNNER(connection)
{
	RUN_TEST_CASE(connection, Init);
	RUN_TEST_CASE(connection, CleanUp);
	RUN_TEST_CASE(connection, InitHeaders);
	RUN_TEST_CASE(connection, CleanUpHeaders);
	RUN_TEST_CASE(connection, PrepareData);
}

TEST_GROUP_RUNNER(tools)
{
	RUN_TEST_CASE(tools, AppendString);
	RUN_TEST_CASE(tools, AppendData);
}

static void run_tests(void)
{
	RUN_TEST_GROUP(config);
	RUN_TEST_GROUP(sensor);
	RUN_TEST_GROUP(connection);
	RUN_TEST_GROUP(tools);
}

int main(int argc, const char* argv[]) { return UnityMain(argc, argv, run_tests); }
