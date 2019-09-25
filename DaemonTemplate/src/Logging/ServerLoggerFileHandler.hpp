#pragma once

#include <bits/stdc++.h>
#include <iostream>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <syslog.h>
#include <unistd.h>

using namespace std;

class ServerLoggerFileHandler {

  private:
    string logFilePath;
    string applicatinName;

    std::ofstream file;

  public:
    static ServerLoggerFileHandler& getInstance();
    void setProperies(string logFilePath, string applicatinName);

    ServerLoggerFileHandler(ServerLoggerFileHandler const&) = delete;
    void operator=(ServerLoggerFileHandler const&) = delete;
    void handleLogString(string logMessage);

  private:
    ServerLoggerFileHandler();
    ~ServerLoggerFileHandler();

    string createDate();
    string numberToStringWithFixedLength(const int i, const int length);
};