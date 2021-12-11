#include <iostream>

#include "rest/dummy.hpp"

int main(int argc, char** argv) {
    std::cout << "dummy value is: " << rest::this_is_dummy_library_function() << std::endl;

    return 0;
}