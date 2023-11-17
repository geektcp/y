//
// Created by geektcp on 11/12/23.
//

#include "HttpRequest.h"
#include "HttpManager.h"
#include "RestClient.h"

static HttpRequest* httpRequest = nullptr;

HttpRequest* HttpRequest::GetInstance()
{
    if(httpRequest == nullptr){
        httpRequest = new HttpRequest();
    }
    return httpRequest;
}

HttpRequest::HttpRequest()
{
}

HttpRequest::~HttpRequest()
{
}


/**
 * Performs a non-blocking HTTP request.
 *
 * When the passed callback function is called, the parameters `(status, body, headers)` are passed to it.
 *
 *     -- GET example (prints a random word)
 *     HttpRequest("GET", "https://random-word-api.herokuapp.com/word", function(status, body, headers)
 *         print("Random word: " .. string.sub(body, 3, body:len() - 2))
 *     end)
 *
 *     -- POST example with JSON request body
 *     HttpRequest("POST", "https://jsonplaceholder.typicode.com/posts", '{"userId": 1,"title": "Foo","body": "Bar!"}', "application/json", function(status, body, headers)
 *         print(body)
 *     end)
 *
 *     -- Example with request headers
 *     HttpRequest("GET", "https://postman-echo.com/headers", { Accept = "application/json", ["User-Agent"] = "Eluna Lua Engine" }, function(status, body, headers)
 *         print(body)
 *     end)
 *
 * @proto (httpMethod, url, function)
 * @proto (httpMethod, url, headers, function)
 * @proto (httpMethod, url, body, contentType, function)
 * @proto (httpMethod, url, body, contentType, headers, function)
 *
 * @param string httpMethod : the HTTP method to use (possible values are: `"GET"`, `"HEAD"`, `"POST"`, `"PUT"`, `"PATCH"`, `"DELETE"`, `"OPTIONS"`)
 * @param string url : the URL to query
 * @param table headers : a table with string key-value pairs containing the request headers
 * @param string body : the request's body (only used for POST, PUT and PATCH requests)
 * @param string contentType : the body's content-type
 * @param function function : function that will be called when the request is executed
 */


int HttpRequest::RequestAsync(
        std::string url
        )
{
    return HttpRequest::RequestAsync("GET", std::move(url));
}

int HttpRequest::RequestAsync(
        std::string method,
        std::string url)
{
    return HttpRequest::RequestAsync(std::move(method), std::move(url), "");
}

int HttpRequest::RequestAsync(
        std::string method,
        std::string url,
        std::string body)
{
    std::map<std::string, std::string> headers;
    headers.insert(std::pair<std::string, std::string>("Content-Type", "application/json"));
    return HttpRequest::RequestAsync(std::move(method), std::move(url), std::move(body), headers);
}

int HttpRequest::RequestAsync(
        std::string method,
        std::string url,
        std::string body,
        std::map<std::string, std::string> headers)
{
    HttpManager* httpManager = HttpManager::GetInstance();
    auto req = new HttpWorkItem(0, method, url, body, headers);
    httpManager->PushRequest(req);
    delete req;
    std::this_thread::sleep_for(std::chrono::seconds(3));   // should be comment

    return 0;
}


///////////////////////////////////////////////////////////////////////////
RestClient::Response HttpRequest::RequestDirect(std::string url)
{
    return HttpRequest::RequestDirect("GET", std::move(url));
}

RestClient::Response HttpRequest::RequestDirect(std::string method,
                                            std::string url)
{
    return HttpRequest::RequestDirect(std::move(method), std::move(url), "");
}

RestClient::Response HttpRequest::RequestDirect(std::string method,
                                            std::string url,
                                            std::string body)
{
    std::map<std::string, std::string> headers;
    headers.insert(std::pair<std::string, std::string>("Content-Type", "application/json"));
    return HttpRequest::RequestDirect(std::move(method), std::move(url), std::move(body), headers);
}

RestClient::Response HttpRequest::RequestDirect(std::string method,
                                            std::string url,
                                            std::string body,
                                            std::map<std::string, std::string> headers)
{
    auto req = new HttpWorkItem(0, method, url, body, headers);
    RestClient::Response response = HttpRequest::RequestDirect(req);
    delete(req);
    return response;
}

RestClient::Response HttpRequest::RequestDirect(HttpWorkItem* req)
{
    RestClient::Connection* client = new RestClient::Connection("");
    if(req->headers.empty()){
        req->headers.insert(std::pair<std::string, std::string>("Content-Type", "application/json"));
    }
    client->SetHeaders(req->headers);
    const std::string path = req->url;
    const std::string method = req->httpVerb;
    const std::string body = req->body;
    if (method == "GET")
    {
        return client->GET(path);
    }
    if (method == "HEAD")
    {
        return client->HEAD(path);
    }
    if (method == "POST")
    {
        return client->POST(path, body);
    }
    if (method == "PUT")
    {
        return client->PUT(path, body);
    }
    if (method == "PATCH")
    {
        return client->PATCH(path, body);
    }
    if (method == "DELETE")
    {
        return client->DELETE(path);
    }
    if (method == "OPTIONS")
    {
        return client->OPTIONS(path);
    }

    printf("[Eluna]: HTTP request error: invalid HTTP verb %s", method.c_str());
    return client->GET(path);
}
