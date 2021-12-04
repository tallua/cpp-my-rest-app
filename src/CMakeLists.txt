cmake_minimum_required(VERSION 3.15)
project(cpp-my-rest-app)

find_package(cpprestsdk REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(GTest REQUIRED)

add_executable(cpp-my-rest-app main.cpp)
target_link_libraries(cpp-my-rest-app cpprestsdk::cpprest OpenSSL::Crypto gtest)
