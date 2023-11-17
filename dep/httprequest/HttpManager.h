#ifndef ELUNA_HTTP_MANAGER_H
#define ELUNA_HTTP_MANAGER_H

#include <regex>

#include "RestClient.h"
#include "SPSCQueue.h"
#include "Connection.h"
#include <thread>
#include <condition_variable>
#include <mutex>

struct HttpWorkItem
{
public:
    HttpWorkItem(int funcRef, const std::string& httpVerb, const std::string& url, const std::string& body);
    HttpWorkItem(int funcRef, const std::string& httpVerb, const std::string& url, const std::string& body, const RestClient::HeaderFields& headers);

    int funcRef;
    std::string httpVerb;
    std::string url;
    std::string body;
    RestClient::HeaderFields headers;
};

struct HttpResponse
{
public:
    HttpResponse(int funcRef, int statusCode, const std::string& body, const RestClient::HeaderFields& headers);

    int funcRef;
    int statusCode;
    std::string body;
    RestClient::HeaderFields headers;
};


class HttpManager
{
public:
    HttpManager();
    ~HttpManager();

    static HttpManager* GetInstance();

    void StartHttpWorker();
    void StopHttpWorker();
    void PushRequest(HttpWorkItem* item);
    void HandleHttpResponses();
    bool ParseUrl(const std::string& url, std::string& host, std::string& path);
    RestClient::Response DoRequest(std::string& url);
    RestClient::Response DoRequest(HttpWorkItem* req);

private:
    void ClearQueues();
    void HttpWorkerThread();

    rigtorp::SPSCQueue<HttpWorkItem*> workQueue;
    rigtorp::SPSCQueue<HttpResponse*> responseQueue;
    std::thread workerThread;
    std::thread responseThread;
    bool startedWorkerThread;
    bool startedResponseThread;
    std::atomic_bool cancelationToken;
    std::condition_variable condVar;
    std::mutex condVarMutex;
    std::regex parseUrlRegex;

    std::atomic_bool cancelationTokenResponse;
    std::condition_variable condVarResponse;
    std::mutex condVarMutexResponse;

};


#endif // #ifndef ELUNA_HTTP_MANAGER_H
