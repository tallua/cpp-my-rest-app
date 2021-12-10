cmake_minimum_required(VERSION 3.15)
project(cpp-my-rest-app-test)

find_package(cpprestsdk REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(GTest REQUIRED)

add_executable(cpp-my-rest-app-test test_main.cpp)
target_link_libraries(cpp-my-rest-app-test cpprestsdk::cpprest OpenSSL::Crypto gtest)
