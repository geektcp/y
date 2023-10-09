#include "example.h"
#include "spdlog/spdlog.h"

Dummy::Dummy() {

}


bool Dummy::doSomething() {
    spdlog::info("Welcome to spdlog!");
    // Do silly things, using some C++17 features to enforce C++17 builds only.
    constexpr int digits[2] = {0, 1};
    auto [zero, one] = digits;
    return zero + one;
}


