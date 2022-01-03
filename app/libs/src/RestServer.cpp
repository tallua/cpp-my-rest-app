#include "rest/core/RestServer.hpp"

#include <iostream>
#include <string_view>

using namespace web::http;

namespace rest
{
namespace core
{

Request::Request(web::http::http_request& req)
    : rest_request(req)
{
}

const web::http::uri& Request::uri() const
{
    return rest_request.request_uri();
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


Handlers::const_iterator Handlers::find(const std::string& url) const
{
    auto fixed_it = fixed_handlers.find(url);
    if (fixed_it != fixed_handlers.end()) {
        return Handlers::const_iterator(std::addressof(fixed_it->second));
    }

    auto wild_it = std::find_if(wildcard_handlers.begin(), wildcard_handlers.end(), [&](WildcardHandler wildcard) {
        return std::string_view(url).substr(0, wildcard.url.size()) == wildcard.url;
    });
    if (wild_it != wildcard_handlers.end()) {
        return Handlers::const_iterator(std::addressof(wild_it->handler));
    }

    return Handlers::const_iterator(nullptr);
}


Handlers::const_iterator Handlers::end() const
{
    return Handlers::const_iterator(nullptr);
}

void Handlers::insert(const std::string& url, SynchronizedHandler handler)
{
    if (!url.empty() && url.back() == '*') {
        wildcard_handlers.push_back({ url.substr(0, url.size() - 1), handler });
    } else {
        fixed_handlers[url] = handler;
    }
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

        if (!(*handler_it)) {
            message.reply(status_codes::NotFound);
            return;
        }

            const auto response = (*handler_it)(message);
            message.reply(response.response());
    });
    listener.support(web::http::methods::POST, [&](http_request message) {
        const auto uri = message.request_uri().to_string();
        auto handler_it = set_handlers.find(uri);
        if (handler_it == set_handlers.end()) {
            message.reply(status_codes::NotFound);
            return;
        }

        if (!(*handler_it)) {
            message.reply(status_codes::NotFound);
            return;
        }

            const auto response = (*handler_it)(message);
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
    get_handlers.insert(url, handler);
}

void RestServer::OnPost(const std::string& url, SynchronizedHandler handler)
{
    set_handlers.insert(url, handler);
}


}
}

