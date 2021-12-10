cmake_minimum_required(VERSION 3.15)

add_subdirectory(src)
add_subdirectory(tests)

enable_testing()
add_test(NAME cpp-my-rest-app-test COMMAND ./cpp-my-rest-app-test)