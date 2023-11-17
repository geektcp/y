#include <thread>
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
}

#if defined TRINITY || defined AZEROTHCORE
#define CPPHTTPLIB_OPENSSL_SUPPORT
#endif
#include "HttpManager.h"
#include <thread>
#include "RestClient.h"


/**
 * static member variable must declare cpp file ,not is the head file
 * if not ,will report undefined reference to static variable
 */
static HttpManager* httpManager = nullptr;

HttpManager* HttpManager::GetInstance()
{
    if(httpManager == nullptr){
        httpManager = new HttpManager();
    }
    return httpManager;
}
HttpWorkItem::HttpWorkItem(int funcRef, const std::string& httpVerb, const std::string& url, const std::string& body)
        : funcRef(funcRef),
          httpVerb(httpVerb),
          url(url),
          body(body)
{ }

HttpWorkItem::HttpWorkItem(int funcRef, const std::string& httpVerb, const std::string& url, const std::string& body, const RestClient::HeaderFields& headers)
        : funcRef(funcRef),
          httpVerb(httpVerb),
          url(url),
          body(body),
          headers(headers)
{ }

HttpResponse::HttpResponse(int funcRef, int statusCode, const std::string& body, const RestClient::HeaderFields& headers)
        : funcRef(funcRef),
          statusCode(statusCode),
          body(body),
          headers(headers)
{ }

HttpManager::HttpManager()
        : workQueue(16),
          startedWorkerThread(false),
          cancelationToken(false),
          condVar(),
          condVarMutex(),
          responseQueue(16),
          startedResponseThread(false),
          cancelationTokenResponse(false),
          condVarResponse(),
          condVarMutexResponse(),
          parseUrlRegex("^(([^:/?#]+):)?(//([^/?#]*))?([^?#]*)(\\?([^#]*))?(#(.*))?")
{
    httpManager = nullptr;
    StartHttpWorker();
}

HttpManager::~HttpManager()
{
    StopHttpWorker();
}

void HttpManager::PushRequest(HttpWorkItem* item)
{
    std::unique_lock<std::mutex> lock(condVarMutex);
    workQueue.push(item);
    condVar.notify_one();
}

void HttpManager::StartHttpWorker()
{
    printf("StartHttpWorker start\n");
    ClearQueues();

    if (!startedWorkerThread)
    {
        cancelationToken.store(false);
        workerThread = std::thread(&HttpManager::HttpWorkerThread, this);
        startedWorkerThread = true;
        responseThread = std::thread(&HttpManager::HandleHttpResponses, this);
        startedResponseThread = true;
    }
}

void HttpManager::ClearQueues()
{
    while (workQueue.front())
    {
        HttpWorkItem* item = *workQueue.front();
        if (item != nullptr)
        {
            delete item;
        }
        workQueue.pop();
    }

    while (responseQueue.front())
    {
        HttpResponse* item = *responseQueue.front();
        if (item != nullptr)
        {
            delete item;
        }
        responseQueue.pop();
    }
}

void HttpManager::StopHttpWorker()
{
    if (!startedWorkerThread)
    {
        return;
    }

    startedWorkerThread = false;
    cancelationToken.store(true);
    condVar.notify_one();
    workerThread.join();

    startedResponseThread = false;
    cancelationTokenResponse.store(true);
    condVarResponse.notify_one();
    responseThread.join();

    ClearQueues();
}

void HttpManager::HttpWorkerThread()
{
    printf("HttpWorkerThread start\n");
    while (true)
    {
        printf("while start\n");
        {
            std::unique_lock<std::mutex> lock(condVarMutex);
            condVar.wait(lock, [&] { return workQueue.front() != nullptr || cancelationToken.load(); });
        }

        if (cancelationToken.load())
        {
            break;
        }
        if (!workQueue.front())
        {
            continue;
        }

        HttpWorkItem* req = *workQueue.front();
        workQueue.pop();
        if (!req)
        {
            continue;
        }
        RestClient::Response response;
        try
        {
            printf("request start\n");
            std::string url = "http://postman-echo.com/headers";
            response = RestClient::GET(url);

            if (response.code == 301)
            {
                std::string location = response.headers["Location"];
                response = RestClient::GET(location);
            }
        }
        catch (const std::exception& ex)
        {
            printf("[exception]: HTTP request error: %s", ex.what());
        }
        std::unique_lock<std::mutex> lock(condVarMutexResponse);
        responseQueue.push(new HttpResponse(req->funcRef, response.code, response.body, response.headers));
        condVarResponse.notify_one();
    }
}

bool HttpManager::ParseUrl(const std::string& url, std::string& host, std::string& path)
{
    std::smatch matches;

    if (!std::regex_search(url, matches, parseUrlRegex))
    {
        return false;
    }

    std::string scheme = matches[2];
    std::string authority = matches[4];
    std::string query = matches[7];
    host = scheme + "://" + authority;
    path = matches[5];
    if (path.empty())
    {
        path = "/";
    }
    path += (query.empty() ? "" : "?") + query;

    return true;
}

void HttpManager::HandleHttpResponses()
{
    while (true)
    {
        if(responseQueue.empty()){
            std::this_thread::sleep_for(std::chrono::seconds(3));
            continue;
        }
        {
            std::unique_lock<std::mutex> lock(condVarMutexResponse);
            condVarResponse.wait(lock, [&] { return responseQueue.front() != nullptr || cancelationTokenResponse.load(); });
        }

        if (cancelationTokenResponse.load())
        {
            break;
        }
        if (!responseQueue.front())
        {
            continue;
        }
        HttpResponse* res = *responseQueue.front();
        responseQueue.pop();
//
        if (res == nullptr)
        {
            printf("nullptr!\n");
            continue;
        }
        printf("HandleHttpResponses %d\n", res->statusCode);
        printf("HandleHttpResponses %s\n", res->body.c_str());
        delete res;
    }
}
