#include "Dummy.h"
#include "spdlog/spdlog.h"


bool Dummy::DoSomething() {
    spdlog::info("Welcome to Y !");
    Init(3, 2);
    // Do silly things, using some C++17 features to enforce C++17 builds only.
    constexpr int digits[2] = {0, 1};
    auto [zero, one] = digits;
    return zero + one < 17;
}


void Dummy::Init(unsigned int constAccountId, unsigned int constGuid){
    unsigned int& accountId = constAccountId;
    unsigned int& guid = constGuid;
    spdlog::info("constAccountId: {} | constGuid: {}",constAccountId, constGuid);
    spdlog::info("accountId: {} | guid: {}",accountId, guid);
}
