
#include "Daemon.hpp"
#include "ExampleModule/ExampleModule.hpp"
#include "Logging/Logger.hpp"
#include "Logging/LoggingProcessor.hpp"
#include "SignalHandler/KillSignalHandler.hpp"

#include "ArgumentParser/ArgumentParser.hpp"

#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

void configLogging(const string applicatinName, ArgumentParser parser) {
    string logFilePath;
    if (parser.exitsCommandOption("--logFilePath")) {
        logFilePath = parser.getCommandOption("--logFilePath");
    } else {
        logFilePath = "/var/log/daemon/";
    }

    LoggingProcessor& loggingProcessor = LoggingProcessor::getInstance();
    loggingProcessor.setProperies(logFilePath, applicatinName);
    loggingProcessor.enableTermial();
    loggingProcessor.enableFilelog();
    // loggingProcessor.enableSyslog();
}

int main(const int argc, const char** argv) {
    string logtag = "main";
    string applicatinName = "daemonTemplate";

    ArgumentParser parser(argc, argv);
    configLogging(applicatinName, parser);

    try {
        KillSignalHandler killSignalHandler;

        while (!killSignalHandler.isKillSignalReceived()) {
            Log::i(logtag, "message");
            std::this_thread::sleep_for(2s);
        }
        return EXIT_SUCCESS;

    } catch (KillSignalException& e) {
        Log::e(logtag, "KillSignalHandler: ");
        std::cerr << "KillSignalHandler: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}