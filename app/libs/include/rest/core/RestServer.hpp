#pragma once

#include <string>
#include <functional>

#include <cpprest/http_msg.h>
#include <cpprest/http_listener.h>

namespace rest
{
namespace core
{

struct Request {
    Request() = default;
    Request(web::http::http_request& req);
};

struct Response {
    Response();
    Response(const std::string& message);

    web::http::status_code code() const { return rest_response.status_code(); }

    const web::http::http_response& response() const { return rest_response; }

private:
    web::http::http_response rest_response;
};

inline bool operator == (const Response& lhs, const Response& rhs)
{
    return false;
}

using SynchronizedHandler = std::function<Response(const Request& req)>;

class RestServer
{
public:
    RestServer(const std::string& url);
    ~RestServer();

    RestServer(const RestServer&) = delete;
    RestServer(RestServer&&) = delete;

    RestServer& operator= (const RestServer&) = delete;
    RestServer& operator= (RestServer&&) = delete;

    void Run();

    void OnGet(const std::string& url, SynchronizedHandler handler);
    void OnPost(const std::string& url, SynchronizedHandler handler);
private:
    SynchronizedHandler get_handler;
    SynchronizedHandler set_handler;

    web::http::experimental::listener::http_listener listener;
};


}
}