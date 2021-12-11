cmake_minimum_required(VERSION 3.15)
project(cpp-my-rest-app-root NONE)

add_subdirectory(src)

enable_testing()
add_subdirectory(tests)