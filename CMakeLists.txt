cmake_minimum_required(VERSION 3.16)

project(senseBox C)

set(CMAKE_C_STANDARD 99)

find_package(CURL REQUIRED)

include_directories(
    extern/bme280
    src
)

add_executable(
    senseBox

    extern/bme280/bme280.c

    src/sensor.c
    src/config.c
    src/connection.c

    src/main.c
)

target_link_libraries(
    senseBox

    PRIVATE curl
)

add_custom_command(
    TARGET senseBox POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/box.config
    ${CMAKE_CURRENT_BINARY_DIR}/box.config
)