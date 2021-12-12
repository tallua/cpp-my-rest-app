cmake_minimum_required(VERSION 3.15)
project(cpp-my-rest-libs)

set(SOURCES
    src/dummy.cpp
    src/RestServer.cpp
)

## Rest
find_package(cpprestsdk REQUIRED)
find_package(OpenSSL REQUIRED)

add_library(cpp-my-rest-libs ${SOURCES})
target_link_libraries(cpp-my-rest-libs
    cpprestsdk::cpprest
    OpenSSL::Crypto
)
target_include_directories(cpp-my-rest-libs PUBLIC include)
