cmake_minimum_required(VERSION 3.2.2)
project(udevpp C CXX)
set(EXECUTABLE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
add_definitions(-std=c++17)
add_compile_options(-Wall -Wextra -Wpedantic)

option(UDEVPP_BUILD_EXAMPLES "Build examples for udevpp" ON)

file(GLOB SOURCES "src/*cpp" "include/*h")
find_package(UDev REQUIRED)

add_library(udevpp ${SOURCES})

target_include_directories(udevpp PRIVATE ${UDEV_INCLUDE_DIR})
target_include_directories(udevpp PUBLIC include)

target_link_libraries(udevpp PRIVATE ${UDEV_LIBRARIES})

IF (UDEVPP_BUILD_EXAMPLES)
    add_executable(example_udevpp examples/example_udevpp.cpp)
    target_include_directories(example_udevpp PUBLIC include)
    target_link_libraries(example_udevpp PRIVATE udevpp)
ENDIF()

# enable_testing()
# configure_file(tests/tests.conf tests/tests.conf)
# file(GLOB TEST_FILES "tests/catch.hpp" "tests/*cpp")
# add_executable(udevpp_tests ${TEST_FILES})
# target_link_libraries(udevpp_tests udevpp)
# add_test(CatchTests udevpp_tests)
