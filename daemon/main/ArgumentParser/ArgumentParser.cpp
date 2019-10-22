#include "ArgumentParser.hpp"

ArgumentParser::ArgumentParser(const int argc, const char* argv[]) {
    for (int i = 0; i < argc; ++i) {
        this->tokens.push_back(string(argv[i]));
    }
}

ArgumentParser::~ArgumentParser() {
}

string ArgumentParser::getCommandOption(const string option) {
    std::vector<std::string>::const_iterator itr;

    itr = std::find(this->tokens.begin(), this->tokens.end(), option);

    if (itr != this->tokens.end() && ++itr != this->tokens.end()) {
        return *itr;
    }

    static const std::string empty_string("");
    return empty_string;
}

bool ArgumentParser::exitsCommandOption(const string option) {
    return std::find(this->tokens.begin(), this->tokens.end(), option) != this->tokens.end();
}