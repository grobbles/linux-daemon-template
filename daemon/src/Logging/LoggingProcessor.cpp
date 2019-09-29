#include "LoggingProcessor.hpp"

LoggingProcessor::LoggingProcessor() {
}

LoggingProcessor::~LoggingProcessor() {
    closelog();
}

LoggingProcessor& LoggingProcessor::getInstance() {
    static LoggingProcessor instance;
    return instance;
}

void LoggingProcessor::enableFilelog() {
    this->isFilelogEnable = true;

    struct stat st;
    if (stat(logFilePath.c_str(), &st) != 0) {
        if (mkdir(logFilePath.c_str(), 0777) == -1) {
            std::cout << "Error: The path could not be created. " << std::endl;
        }
    } else {
        std::cout << "The path is pesent." << std::endl;
    }

    string date = createDate();
    string logFileName = date + "_" + applicatinName + ".log";
    this->file = ofstream(logFilePath + logFileName);
}

void LoggingProcessor::enableSyslog() {
    this->isSyslogEnable = true;
    openlog(this->applicatinName.c_str(), LOG_PID | LOG_CONS, LOG_DAEMON);
}

void LoggingProcessor::enableTermial() {
    this->isTermialEnable = true;
}

void LoggingProcessor::handleLogString(string logMessage) {
    if (this->isTermialEnable) {
        std::cout << logMessage << std::endl;
    }

    if (this->isFilelogEnable) {
        if (!this->file.is_open()) {
            std::cout << "error the file is not open " << std::endl;
            return;
        }
        this->file << logMessage;
        this->file.flush();
    }

    if (this->isSyslogEnable) {
        syslog(LOG_INFO, logMessage.c_str());
    }
}

void LoggingProcessor::setProperies(string logFilePath, string applicatinName) {
    this->logFilePath = logFilePath;
    this->applicatinName = applicatinName;
}

string LoggingProcessor::createDate() {
    time_t now = time(0);
    tm* localTime = localtime(&now);

    string year = numberToStringWithFixedLength(localTime->tm_year + 1900, 4);
    string mouth = numberToStringWithFixedLength(localTime->tm_mon + 1, 2);
    string day = numberToStringWithFixedLength(localTime->tm_mday, 2);
    string hour = numberToStringWithFixedLength(localTime->tm_hour, 2);
    string minutes = numberToStringWithFixedLength(localTime->tm_min, 2);

    string date = year + "-" + mouth + "-" + day + "---" + hour + "-" + minutes;
    return date;
}
string LoggingProcessor::numberToStringWithFixedLength(const int i, const int length) {
    std::ostringstream ostr;
    if (i < 0) {
        ostr << '-';
    }

    ostr << std::setfill('0') << std::setw(length) << (i < 0 ? -i : i);
    return ostr.str();
}