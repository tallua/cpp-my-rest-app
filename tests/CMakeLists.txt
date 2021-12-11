cmake_minimum_required(VERSION 3.15)
project(cpp-my-rest-tests)

set(CMAKE_CXX_STANDARD 17)

## GTEST
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)


## Test Binary
enable_testing()

add_executable(cpp-my-rest-tests test_main.cpp)
target_link_libraries(cpp-my-rest-tests gtest_main)

gtest_discover_tests(cpp-my-rest-tests)