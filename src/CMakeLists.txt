cmake_minimum_required(VERSION 3.15)
project(cpp-my-rest-app)

find_package(cpprestsdk REQUIRED)
find_package(OpenSSL REQUIRED)

set(SOURCES)

add_executable(cpp-my-rest-app main.cpp ${SOURCES})
target_link_libraries(cpp-my-rest-app cpprestsdk::cpprest OpenSSL::Crypto)
