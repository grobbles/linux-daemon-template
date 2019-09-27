/*
 * Logger.hpp
 *
 *  Created on: Apr 8, 2019
 *      Author: roder
 */

#ifndef LOGGING_LOGGER_HPP_
#define LOGGING_LOGGER_HPP_

#include <bits/stdc++.h>
#include <chrono>
#include <ctime>
#include <inttypes.h>
#include <iostream>
#include <pthread.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include "LoggingProcessor.hpp"

using namespace std;

enum LogLevel { VERBOSE, DEBUG, INFO, WARN, ERROR };

class Log {
  public:
    static void v(string logTag, string logMessage);
    static void d(string logTag, string logMessage);
    static void i(string logTag, string logMessage);
    static void w(string logTag, string logMessage);
    static void e(string logTag, string logMessage);

  private:
    static void stringOutput(string loggingMessage);
    static string getCurrentDate();
    static string createMetaInformation(string date, string logtag, string logLevel);
    static int getMilliseconds();
};

#endif /* LOGGING_LOGGER_HPP_ */
