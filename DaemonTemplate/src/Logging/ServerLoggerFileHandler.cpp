#include "ServerLoggerFileHandler.hpp"

ServerLoggerFileHandler::ServerLoggerFileHandler() {
}

ServerLoggerFileHandler::~ServerLoggerFileHandler() {
    closelog();
}

ServerLoggerFileHandler& ServerLoggerFileHandler::getInstance() {
    static ServerLoggerFileHandler instance;
    return instance;
}

void ServerLoggerFileHandler::handleLogString(string logMessage) {
    syslog(LOG_INFO, logMessage.c_str());

    if (!this->file.is_open()) {
        std::cout << "error the file is not open " << std::endl;
        return;
    }
    this->file << logMessage;
    this->file.flush();
}

void ServerLoggerFileHandler::setProperies(string logFilePath, string applicatinName) {
    openlog(this->applicatinName.c_str(), LOG_PID | LOG_CONS, LOG_DAEMON);

    this->logFilePath = logFilePath;
    this->applicatinName = applicatinName;

    if (mkdir(logFilePath.c_str(), 0777) == -1) {

    } else {
        std::cout << "Error: The path could not be created. " << std::endl;
    }

    string date = createDate();
    string logFileName = date + "_" + applicatinName + ".log";
    this->file = ofstream(logFilePath + logFileName);
}

string ServerLoggerFileHandler::createDate() {
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
string ServerLoggerFileHandler::numberToStringWithFixedLength(const int i, const int length) {
    std::ostringstream ostr;
    if (i < 0) {
        ostr << '-';
    }

    ostr << std::setfill('0') << std::setw(length) << (i < 0 ? -i : i);
    return ostr.str();
}