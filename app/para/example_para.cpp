//
// Created by geektcp on 11/12/23.
//

#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#endif

#include "Common.h"
#include "HttpRequest.h"
#include <iostream>
#include <stdexcept>
#include <signal.h>
#include <boost/stacktrace.hpp>

void print_stacktrace(int signum) {
    ::signal(signum, SIG_DFL);
    printf("Stack trace:\n%s\n", boost::stacktrace::to_string(boost::stacktrace::stacktrace()).c_str());
    ::raise(SIGABRT);
}

void crash2222 ()
{
    char* aaa = nullptr;
    std::string bbb(aaa);
    std::vector<double> x(5);
    for (int i =0; i < 100; ++ i)
        x[i] += 3.0 * i;
}

//void handle_eptr(std::exception_ptr eptr) // passing by value is ok
//{
//    try {
//        if (eptr) {
//            std::rethrow_exception(eptr);
//        }
//    } catch(const std::exception& e) {
//        std::cout <<"Caught exception "" << e.what() <<";
//        std::cout<< boost::stacktrace::stacktrace() <<std::endl;
//    }
//}
/*
 */
int main() {
    ::signal(SIGSEGV, &print_stacktrace);
    ::signal(SIGABRT, &print_stacktrace);

//    spdlog::info("test httpclient {} !", "any api");

//    crash2222();


//    try {
//        throw 11;
//    } catch (const std::exception& exc) {
//        eptr = std::current_exception(); // capture
//    }
//    handle_eptr(eptr);
    HttpRequest httpRequest;
//    httpRequest.request();
    httpRequest.rest();

    return 0;
}


