#include "rest/core/RestServer.hpp"

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
}

RestServer::~RestServer()
{
    listener.close();
}


void RestServer::Run()
{
    listener.open();
}

void RestServer::OnGet(const std::string& url, SynchronizedHandler handler)
{
    get_handler = handler;
    listener.support(web::http::methods::GET, [&](http_request message) {
        auto resp = get_handler(Request());
        message.reply(resp.response());
    });
}

void RestServer::OnPost(const std::string& url, SynchronizedHandler handler)
{
    set_handler = handler;
    listener.support(web::http::methods::POST, [&](http_request message) {
        auto resp = set_handler(Request());
        message.reply(resp.response());
    });
}


}
}

