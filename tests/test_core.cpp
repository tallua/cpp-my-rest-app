#include <gtest/gtest.h>

#include <cpprest/http_client.h>

#include "rest/core/RestServer.hpp"

namespace {

using namespace web::http;
using namespace web::http::client;
using namespace rest::core;

http_response request_get(const std::string& host, const std::string& url)
{
    http_client client(host);

    uri_builder builder(url);
    auto req = client.request(methods::GET, builder.to_string());

    req.wait();

    return req.get();
}

http_response request_post(const std::string& host, const std::string& url)
{
    http_client client(host);

    uri_builder builder(url);
    auto req = client.request(methods::POST, builder.to_string());

    req.wait();

    return req.get();
}

TEST(RestServer, test_get_p)
{
    const std::string expect_response("response of test_get");

    RestServer server(U("http://0.0.0.0:1234"));
    server.OnGet("/test_url", [&](auto req) { return expect_response; });
    server.Run();

    const auto actual_response = request_get("http://0.0.0.0:1234", "/test_url");

    EXPECT_EQ(status_codes::OK, actual_response.status_code());
    EXPECT_EQ(expect_response, actual_response.extract_string().get());
}

TEST(RestServer, test_post_p)
{
    const std::string expect_response("response of test_post");

    RestServer server(U("http://0.0.0.0:1234"));
    server.OnPost("/test_url", [&](auto req) { return expect_response; });
    server.Run();

    const auto actual_response = request_post("http://0.0.0.0:1234", "/test_url");

    EXPECT_EQ(status_codes::OK, actual_response.status_code());
    EXPECT_EQ(expect_response, actual_response.extract_string().get());
}

TEST(RestServer, test_no_url)
{
    RestServer server(U("http://0.0.0.0:1234"));
    server.Run();

    const auto get_response = request_get("http://0.0.0.0:1234", "/no_url");
    const auto post_response = request_post("http://0.0.0.0:1234", "/no_url");

    EXPECT_EQ(status_codes::NotFound, get_response.status_code());
    EXPECT_EQ(status_codes::NotFound, post_response.status_code());
}

TEST(RestServer, url_distribute)
{
    const std::string expect_response1("response 1");
    const std::string expect_response2("response 2");

    RestServer server(U("http://0.0.0.0:1234"));
    server.OnGet("/url1", [&](auto req) { return expect_response1; });
    server.OnGet("/url2", [&](auto req) { return expect_response2; });
    server.Run();

    const auto actual_response1 = request_get("http://0.0.0.0:1234", "/url1");
    EXPECT_EQ(status_codes::OK, actual_response1.status_code());
    EXPECT_EQ(expect_response1, actual_response1.extract_string().get());

    const auto actual_response2 = request_get("http://0.0.0.0:1234", "/url2");
    EXPECT_EQ(status_codes::OK, actual_response2.status_code());
    EXPECT_EQ(actual_response2, actual_response2.extract_string().get());
}

TEST(RestServer, throws_exception)
{
    RestServer server(U("http://0.0.0.0:1234"));
    server.OnGet("/test_url", [&](auto req) -> rest::core::Response { throw std::exception(); });
    server.Run();

    const auto actual_response = request_get("http://0.0.0.0:1234", "/test_url");

    EXPECT_EQ(status_codes::InternalError, actual_response.status_code());
}

TEST(RestServer, exception_tolerant)
{
    const std::string expect_response("good response after exception");

    RestServer server(U("http://0.0.0.0:1234"));
    server.OnGet("/test_url", [&, call_count = int(0)](auto req) mutable {
        ++call_count;
        if(call_count == 1)
            throw std::exception();
        return rest::core::Response(expect_response);
    });
    server.Run();

    const auto actual_response1 = request_get("http://0.0.0.0:1234", "/test_url");
    EXPECT_EQ(status_codes::InternalError, actual_response1.status_code());

    const auto actual_response2 = request_get("http://0.0.0.0:1234", "/test_url");
    EXPECT_EQ(status_codes::OK, actual_response2.status_code());
    EXPECT_EQ(expect_response, actual_response2.extract_string().get());
}

}
