// External
#include "unity_fixture.h"

TEST_GROUP_RUNNER(config) { RUN_TEST_CASE(config, ParseConfig); }

static void run_tests(void) { RUN_TEST_GROUP(config); }

int main(int argc, const char* argv[]) { return UnityMain(argc, argv, run_tests); }

