cmake_minimum_required(VERSION 3.16)

project(senseBox C)

set(CMAKE_C_STANDARD 99)

find_package(CURL REQUIRED)

# Release

add_executable(
    senseBox

    extern/bme280/bme280.c

    src/config.c
    src/sensor.c
    src/connection.c
    src/tools.c

    src/main.c
)

target_include_directories(
    senseBox

    PRIVATE extern/bme280
    PRIVATE src
)

target_link_libraries(
    senseBox

    PRIVATE curl
)

# Tests

add_executable(
    Tests

    extern/Unity/src/unity.c
    extern/Unity/extras/fixture/src/unity_fixture.c
    extern/Unity/extras/memory/src/unity_memory.c

    extern/bme280/bme280.c

    src/config.c
    src/sensor.c
    src/connection.c
    src/tools.c

    test/config_test.c
    test/connection_test.c
    test/tools_test.c

    test/main_test.c
)

target_compile_definitions(
    Tests

    PRIVATE TESTS=1
)

target_include_directories(
    Tests

    PRIVATE extern/Unity/src
    PRIVATE extern/Unity/extras/fixture/src
    PRIVATE extern/Unity/extras/memory/src
    PRIVATE extern/bme280
    PRIVATE src
    PRIVATE test
)

target_compile_options(
    Tests

    PRIVATE --coverage
)

target_link_libraries(
    Tests

    PRIVATE gcov
    PRIVATE curl
)