#include "Dummy.h"
#include "spdlog/spdlog.h"
#include <iostream>
#include <functional>

using namespace std;

struct Foo{
    void print_sum(int n1, int n2, int n3){
        std::cout << "sum = " << n1 + n2 + n3 << std::endl;
    }
};

void print(int &n1, int &n2, int &n3){
    n1++;
    n2++;
    n3++;
}

bool Dummy::DoSomething() {
    spdlog::info("Welcome to Y !");
    Init(3, 2);
    // Do silly things, using some C++17 features to enforce C++17 builds only.
    constexpr int digits[2] = {0, 1};
    auto [zero, one] = digits;
    return zero + one < 17;
}


void Dummy::Init(uint32 constAccountId, uint32 constGuid){
    uint32& accountId = constAccountId;
    uint32& guid = constGuid;
    spdlog::info("constAccountId: {} | constGuid: {}",constAccountId, constGuid);
    spdlog::info("accountId: {} | guid: {}",accountId, guid);
}

void Dummy::CallBack()
{
    Foo foo;
    auto callback = std::bind(&Foo::print_sum, &foo, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
    callback(5, 10, 15);
//std::placeholders::_1... // para

    int a = 1, b = 2, c = 3;
    auto func2 = std::bind(print, a, b, std::ref(c));
    func2();
    std::cout <<"a = " << a << endl;
    cout <<"b = " << b << endl;
    cout <<"c = " << c << endl;
};