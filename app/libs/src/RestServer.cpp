#include "rest/core/RestServer.hpp"

#include <iostream>

using namespace web::http;

namespace rest
{
namespace core
{

Request::Request(web::http::http_request& req)
{
}

Response::Response()
    : rest_response(status_codes::OK)
{
}

Response::Response(const std::string& message)
    : rest_response(status_codes::OK)
{
    rest_response.set_body(message);
}

RestServer::RestServer(const std::string& url)
    : listener(url)
{
    listener.support(web::http::methods::GET, [&](http_request message) {
        const auto uri = message.request_uri().to_string();
        auto handler_it = get_handlers.find(uri);
        if (handler_it == get_handlers.end()) {
            message.reply(status_codes::NotFound);
            return;
        }

        if (!handler_it->second) {
            message.reply(status_codes::InternalError);
            return;
        }

        const auto response = handler_it->second(Request(message));
        message.reply(response.response());
    });
    listener.support(web::http::methods::POST, [&](http_request message) {
        const auto uri = message.request_uri().to_string();
        auto handler_it = set_handlers.find(uri);
        if (handler_it == set_handlers.end()) {
            message.reply(status_codes::NotFound);
            return;
        }

        if (!handler_it->second) {
            message.reply(status_codes::InternalError);
            return;
        }

        const auto response = handler_it->second(Request(message));
        message.reply(response.response());
    });
}

RestServer::~RestServer()
{
    listener.close();
}


void RestServer::Run()
{
    listener.open().wait();
}

void RestServer::OnGet(const std::string& url, SynchronizedHandler handler)
{
    get_handlers[url] = handler;
}

void RestServer::OnPost(const std::string& url, SynchronizedHandler handler)
{
    set_handlers[url] = handler;
}


}
}

