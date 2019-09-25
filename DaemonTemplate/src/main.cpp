

#include "Daemon.hpp"
#include "ExampleModule/ExampleModule.hpp"
#include "SignalHandler/KillSignalHandler.hpp"

#include <sys/stat.h>

#define UDS_FILE "/tmp/so./ck.uds"

using namespace std;

int main(int argc, char* argv[]) {
    string logtag = "main";

    string clientLogFileName = "Client.log";
    string applicatinName = "LoggingServer";
    string logFilePath = "/home/uwe/log/";

    // openlog(argv[0], LOG_PID | LOG_CONS, LOG_DAEMON);
    // syslog(LOG_INFO, "Started %s", "app_name");

    // Daemon* daemon = new Daemon();
    // daemon->daemonize();

    syslog(LOG_INFO, "started daemon %s", "app_name");

    // const int dir_err = mkdir("/var/log/LoggingServer/", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    // if (-1 == dir_err) {
    //     syslog(LOG_INFO, "Error creating directory!n");
    //     exit(1);
    // }

    ServerLoggerFileHandler& serverLoggerFileHandler = ServerLoggerFileHandler::getInstance();
    serverLoggerFileHandler.setProperies(logFilePath, applicatinName);

    try {
        KillSignalHandler killSignalHandler;

        while (!killSignalHandler.isKillSignalReceived()) {
            std::this_thread::sleep_for(50ms);
        }
        // delete daemon;

        return EXIT_SUCCESS;

    } catch (KillSignalException& e) {
        Log::e(logtag, "KillSignalHandler: ");
        std::cerr << "KillSignalHandler: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}