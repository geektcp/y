//
// Created by geektcp on 11/12/23.
//

#ifndef EXECUTOR_HTTPREQUEST_H
#define EXECUTOR_HTTPREQUEST_H

#include "HttpManager.h"

class HttpRequest {
public:
    HttpRequest();
    ~HttpRequest();


    static HttpRequest* GetInstance();

    int RequestAsync(
            std::string url
    );

    int RequestAsync(
            std::string method,
            std::string url);

    int RequestAsync(
            std::string method,
            std::string url,
            std::string body);

    int RequestAsync(std::string method,
            std::string url,
            std::string body,
            std::map<std::string, std::string> headers);


    RestClient::Response RequestDirect(
            std::string url
    );

    RestClient::Response RequestDirect(
            std::string method,
            std::string url);

    RestClient::Response RequestDirect(
            std::string method,
            std::string url,
            std::string body);

    RestClient::Response RequestDirect(std::string method,
                     std::string url,
                     std::string body,
                     std::map<std::string, std::string> headers);

    RestClient::Response  RequestDirect(
            HttpWorkItem* url
    );

};


#endif //EXECUTOR_HTTPREQUEST_H
