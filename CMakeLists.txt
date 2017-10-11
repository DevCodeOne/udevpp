cmake_minimum_required(VERSION 3.2.2)
project(udevpp C CXX)
set(EXECUTABLE_BUILD_TYPE Debug)
add_compile_options(-Wall -Wextra -Wpedantic)
add_definitions(-std=c++17)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

include_directories(include)
file(GLOB SOURCES "src/*cpp" "include/*h")
find_package(UDev REQUIRED)

include_directories(${UDEV_INCLUDE_DIR})

add_library(udevpp ${SOURCES})
add_executable(example_udevpp examples/example_udevpp.cpp)

target_link_libraries(udevpp ${UDEV_LIBRARIES})
target_link_libraries(example_udevpp udevpp)

# enable_testing()
# configure_file(tests/tests.conf tests/tests.conf)
# file(GLOB TEST_FILES "tests/catch.hpp" "tests/*cpp")
# add_executable(udevpp_tests ${TEST_FILES})
# target_link_libraries(udevpp_tests udevpp)
# add_test(CatchTests udevpp_tests)
