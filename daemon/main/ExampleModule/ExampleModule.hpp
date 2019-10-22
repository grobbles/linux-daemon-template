#pragma once

#include <set>
#include <string>

#include "../Logging/Logger.hpp"

using namespace std;

class ExampleModule {
  private:
    const string logtag = "ExampleModule";

  public:
    ExampleModule();
    ~ExampleModule();

    int add(int x, int y);
};