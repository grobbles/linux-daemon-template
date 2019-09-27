#pragma once

#include <set>
#include <string>

#include "../Logging/Logger.hpp"

using namespace std;

class ArgumentParser {
  private:
    const string logtag = "ArgumentParser";

    std::vector<std::string> tokens;

  public:
    ArgumentParser(const int argc, const char* argv[]);
    ~ArgumentParser();

    string getCommandOption(const string option);
    bool exitsCommandOption(const string option);
};