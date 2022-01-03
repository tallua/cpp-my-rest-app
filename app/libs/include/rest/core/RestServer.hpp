#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include <functional>

#include <cpprest/http_msg.h>
#include <cpprest/http_listener.h>

namespace rest
{
namespace core
{

struct Request {
    Request(web::http::http_request& req);

    const web::http::uri& uri() const;

private:
    web::http::http_request rest_request;
};

struct Response {
    Response();
    Response(const std::string& message);

    web::http::status_code code() const { return rest_response.status_code(); }

    const web::http::http_response& response() const { return rest_response; }

private:
    web::http::http_response rest_response;
};

using SynchronizedHandler = std::function<Response(const Request& req)>;

class Handlers
{
public:
    struct const_iterator {
        inline bool operator == (const const_iterator& other) const
        {
            return handler == other.handler;
        }

        inline bool operator != (const const_iterator& other) const
        {
            return !(*this == other);
        }

        const SynchronizedHandler& operator* () const { return *handler; }

    private:
        friend class Handlers;
        const_iterator(const SynchronizedHandler* handler) : handler(handler) {}
        const SynchronizedHandler* handler;
    };

    const_iterator find(const std::string& url) const;
    const_iterator end() const;

    void insert(const std::string& url, SynchronizedHandler handler);

private:
    struct WildcardHandler {
        std::string url;
        SynchronizedHandler handler;
    };

    std::vector<WildcardHandler> wildcard_handlers;
    std::unordered_map<std::string, SynchronizedHandler> fixed_handlers;
};

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

    Handlers get_handlers;
    Handlers set_handlers;

    web::http::experimental::listener::http_listener listener;
};


}
}