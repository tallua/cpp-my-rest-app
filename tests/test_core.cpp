#include <gtest/gtest.h>

#include <cpprest/http_client.h>

#include "rest/core/RestServer.hpp"

namespace {

using namespace web::http;
using namespace web::http::client;
using namespace rest::core;

Response request_get(const std::string& host, const std::string& url)
{
    http_client client(host);

    uri_builder builder(url);
    auto req = client.request(methods::GET, builder.to_string());

    req.wait();

    return req.get();
}

Response request_post(const std::string& host, const std::string& url)
{
    http_client client(host);

    uri_builder builder(url);
    auto req = client.request(methods::POST, builder.to_string());

    req.wait();

    return req.get();
}

TEST(RestServer, test_get_p)
{
    const Response expect_response("response of test_get");

    RestServer server(U("http://0.0.0.0:1234"));
    server.OnGet("/test_url", [&](auto req) { return expect_response; });
    server.Run();

    // sleep

    const Response actual_response = request_get("http://0.0.0.0:1234", "/test_url");

    EXPECT_EQ(expect_response, actual_response);
}

TEST(RestServer, test_post_p)
{
    const Response expect_response("response of test_post");

    RestServer server(U("http://0.0.0.0:1234"));
    server.OnPost("/test_url", [&](auto req) { return expect_response; });
    server.Run();

    // sleep

    const Response actual_response = request_post("http://0.0.0.0:1234", "/test_url");

    EXPECT_EQ(expect_response, actual_response);
}

TEST(RestServer, test_no_url)
{
    RestServer server(U("http://0.0.0.0:1234"));
    server.Run();

    // sleep

    const Response get_response = request_get("http://0.0.0.0:1234", "/no_url");
    const Response post_response = request_post("http://0.0.0.0:1234", "/no_url");

    EXPECT_EQ(404, get_response.code());
    EXPECT_EQ(404, post_response.code());
}

}
