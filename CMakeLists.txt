cmake_minimum_required(VERSION 3.15)
project(cpp-my-rest-app)

find_package(cpprestsdk REQUIRED)
find_package(OpenSSL REQUIRED)

add_executable(cpp-my-rest-app src/main.cpp)
target_link_libraries(cpp-my-rest-app cpprestsdk::cpprest OpenSSL::Crypto)
