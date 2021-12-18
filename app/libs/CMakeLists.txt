cmake_minimum_required(VERSION 3.15)
project(cpp-my-rest-libs)

set(SOURCES
    src/dummy.cpp
    src/RestServer.cpp
)

find_package(cpprestsdk REQUIRED)
find_package(OpenSSL REQUIRED)

add_library(cpp-my-rest-libs ${SOURCES})
<<<<<<< HEAD
target_include_directories(cpp-my-rest-libs PUBLIC include)
=======
target_include_directories(cpp-my-rest-libs
    PUBLIC include
)
>>>>>>> main
target_link_libraries(cpp-my-rest-libs
    cpprestsdk::cpprest
    OpenSSL::Crypto
)
