// Executables must have the following defined if the library contains
// doctest definitions. For builds with this disabled, e.g. code shipped to
// users, this can be left out.
#ifdef ENABLE_DOCTEST_IN_LIBRARY
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#endif

#include <iostream>
#include <stdlib.h>

#include "exampleConfig.h"
#include "Dummy.h"
#include "Tlog.h"

#include "spdlog/spdlog.h"

using namespace std;


/*
 * Simple main program that demontrates how access
 * CMake definitions (here the version number) from source code.
 */
int main() {
  spdlog::info("Welcome to X language: {} !", "any thing");

  std::cout << "C++ start from here: "
            << PROJECT_VERSION_MAJOR
            << "."
            << PROJECT_VERSION_MINOR
            << "."
            << PROJECT_VERSION_PATCH
            << "."
            << PROJECT_VERSION_TWEAK
            << std::endl;
  std::system("df -h");

  cout<<__cplusplus<<endl;

  Tlog t = Tlog();
  t.log();

  // Bring in the dummy class from the example source,
  // just to show that it is accessible from main.cpp.
  Dummy d = Dummy();
  int ret = d.doSomething() ? 0 : -1;
  std::cout << "ret: " << ret
          << std::endl;
  return ret;
}
