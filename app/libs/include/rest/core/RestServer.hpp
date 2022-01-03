#pragma once

#include <string>
#include <functional>

#include <cpprest/http_msg.h>

namespace rest
{
namespace core
{

struct Request {
    const web::http::uri& uri() const;
};

struct Response {
    Response(web::http::http_response resp);
    Response(const std::string& message);

    web::http::status_code code() const;
};

using SynchronizedHandler = std::function<Response(const Request& req)>;

class RestServer
{
public:
    RestServer(const std::string& url);
    ~RestServer();

    void Run();

    void OnGet(const std::string& url, SynchronizedHandler handler);
    void OnPost(const std::string& url, SynchronizedHandler handler);
};


}
}