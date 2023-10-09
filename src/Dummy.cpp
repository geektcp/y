#include "Dummy.h"
#include "spdlog/spdlog.h"


bool Dummy::doSomething() {
    spdlog::info("Welcome to Y !");

    // Do silly things, using some C++17 features to enforce C++17 builds only.
    constexpr int digits[2] = {0, 1};
    auto [zero, one] = digits;
    return zero + one < 17;
}


