# C++ My Rest App

## Purpose
c++ study


## Sprints

### API

Our project is to implement following yaml

[YAML](/docs/api.yaml)

### Day 1
 - RestServer class
   - non copyable, movable, may create multiple server

```cpp
class RestServer
{
public:
    // create rest server with given url
    RestServer(const std::string& url);
    // close server. stop if it's running.
    ~RestServer();

    // can handle request after this api
    // doesn't block thread
    void Run();

    // add handler when given url is called with GET method
    void OnGet(const std::string& url, SynchronousHandler handler);

    // add handler when given url is called with POST method
    void OnPost(const std::string& url, SynchronousHandler handler);
};

struct Request {
    const web::http::uri& uri() const;
};

struct Response {
    Response(const std::string& message);

    web::http::status_code code() const;
};

// closure of Response operator() (const Request&) const
typename SynchronousHandler;

class MyRestAppInitialiser
{
    // create a rest server with api
    std::shared_ptr<RestServer> CreateServer();
};
```

### Day2
TBD: apply TDD

TBD: make your own complex handler

### Day3
TBD: attach other module (ex. web parsing)

### Day4
TBD: create real-world application (ex. discord command line bot)

