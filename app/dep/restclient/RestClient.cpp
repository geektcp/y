/**
 * @file restclient.cpp
 * @brief implementation of the restclient class
 *
 * This just provides static wrappers around the Connection class REST
 * methods. However since I didn't want to have to pull in a whole URI parsing
 * library just now, the Connection constructor is passed an empty string and
 * the full URL is passed to the REST methods. All those methods to is
 * concatenate them anyways. So this should do for now.
 *
 * @author Daniel Schauenberg <d@unwiredcouch.com>
 */

#include "RestClient.h"

#include <curl/curl.h>
#if __cplusplus >= 201402L
#include <memory>
#endif

#include "Connection.h"

/**
 * @brief global init function. Call this before you start any threads.
 */
int RestClient::init() {
  CURLcode res = curl_global_init(CURL_GLOBAL_ALL);
  if (res == CURLE_OK) {
    return 0;
  } else {
    return 1;
  }
}

/**
 * @brief global disable function. Call this before you terminate your
 * program.
 */
void RestClient::disable() {
  curl_global_cleanup();
}

/**
 * @brief HTTP GET method
 *
 * @param url to query
 *
 * @return response struct
 */
RestClient::Response RestClient::GET(const std::string& url) {
#if __cplusplus >= 201402L
  auto conn = std::make_unique<RestClient::Connection>("");
  return conn->GET(url);
#else
  RestClient::Response ret;
  RestClient::Connection *conn = new RestClient::Connection("");
  ret = conn->GET(url);
  delete conn;
  return ret;
#endif
}

/**
 * @brief HTTP POST method
 *
 * @param url to query
 * @param ctype content type as string
 * @param data HTTP POST body
 *
 * @return response struct
 */
RestClient::Response RestClient::POST(const std::string& url,
                                      const std::string& ctype,
                                      const std::string& data) {
#if __cplusplus >= 201402L
  auto conn = std::make_unique<RestClient::Connection>("");
  conn->AppendHeader("Content-Type", ctype);
  return conn->POST(url, data);
#else
  RestClient::Response ret;
  RestClient::Connection *conn = new RestClient::Connection("");
  conn->AppendHeader("Content-Type", ctype);
  ret = conn->POST(url, data);
  delete conn;
  return ret;
#endif
}

/**
 * @brief HTTP PUT method
 *
 * @param url to query
 * @param ctype content type as string
 * @param data HTTP PUT body
 *
 * @return response struct
 */
RestClient::Response RestClient::PUT(const std::string& url,
                                     const std::string& ctype,
                                     const std::string& data) {
#if __cplusplus >= 201402L
  auto conn = std::make_unique<RestClient::Connection>("");
  conn->AppendHeader("Content-Type", ctype);
  return conn->PUT(url, data);
#else
  RestClient::Response ret;
  RestClient::Connection *conn = new RestClient::Connection("");
  conn->AppendHeader("Content-Type", ctype);
  ret = conn->PUT(url, data);
  delete conn;
  return ret;
#endif
}

/**
 * @brief HTTP PATCH method
 *
 * @param url to query
 * @param ctype content type as string
 * @param data HTTP PATCH body
 *
 * @return response struct
 */
RestClient::Response RestClient::PATCH(const std::string& url,
                                     const std::string& ctype,
                                     const std::string& data) {
  RestClient::Response ret;
  RestClient::Connection *conn = new RestClient::Connection("");
  conn->AppendHeader("Content-Type", ctype);
  ret = conn->PATCH(url, data);
  delete conn;
  return ret;
}

/**
 * @brief HTTP DELETE method
 *
 * @param url to query
 *
 * @return response struct
 */
RestClient::Response RestClient::DELETE(const std::string& url) {
#if __cplusplus >= 201402L
  auto conn = std::make_unique<RestClient::Connection>("");
  return conn->DELETE(url);
#else
  RestClient::Response ret;
  RestClient::Connection *conn = new RestClient::Connection("");
  ret = conn->DELETE(url);
  delete conn;
  return ret;
#endif
}

/**
 * @brief HTTP HEAD method
 *
 * @param url to query
 *
 * @return response struct
 */
RestClient::Response RestClient::HEAD(const std::string& url) {
#if __cplusplus >= 201402L
  auto conn = std::make_unique<RestClient::Connection>("");
  return conn->HEAD(url);
#else
  RestClient::Response ret;
  RestClient::Connection *conn = new RestClient::Connection("");
  ret = conn->HEAD(url);
  delete conn;
  return ret;
#endif
}

/**
 * @brief HTTP OPTIONS method
 *
 * @param url to query
 *
 * @return response struct
 */
RestClient::Response RestClient::OPTIONS(const std::string& url) {
  RestClient::Response ret;
  RestClient::Connection *conn = new RestClient::Connection("");
  ret = conn->OPTIONS(url);
  delete conn;
  return ret;
}
