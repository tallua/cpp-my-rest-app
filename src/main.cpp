#include <iostream>
#include <cpprest/http_listener.h>

using namespace web::http;
using namespace web::http::experimental::listener;

int main(int argc, char** argv) {
    std::cout << "Hello, Project!!" << std::endl;

    http_listener listener(U("http://0.0.0.0:1234"));

    listener.support(methods::GET, [&listener](const http_request& req) {
        std::cout << "uri: " << req.request_uri().to_string() << std::endl;

        req.reply(status_codes::Accepted, "Hello, Project!!!");
    });

    listener.open();

    while(true);

    return 0;
}