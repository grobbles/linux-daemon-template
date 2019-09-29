#include "Daemon.hpp"

Daemon::Daemon() {
}

Daemon::~Daemon() {
}

void createFork() {
    pid_t pid = 0;

    /* Fork off the parent process */
    pid = fork();

    /* An error occurred */
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    /* Success: Let the parent terminate */
    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }
}

void sessionLeader() {
    /* On success: The child process becomes session leader */
    if (setsid() < 0) {
        exit(EXIT_FAILURE);
    }
}

void irnoreSignals() {
    /* Ignore signal sent from child to parent process */
    signal(SIGCHLD, SIG_IGN);
}

void closeAllOpenFiles() {
    int fd;

    /* Close all open file descriptors */
    for (fd = sysconf(_SC_OPEN_MAX); fd > 0; fd--) {
        close(fd);
    }
}

void setNewFilePermissions() {
    /* Set new file permissions */
    umask(0);
}

void changeWorkDirectory() {
    /* Change the working directory to the root directory */
    /* or another appropriated directory */
    if ((chdir("/")) < 0) {
        exit(EXIT_FAILURE);
    }
}

void Daemon::daemonize() {
    createFork();
    sessionLeader();
    irnoreSignals();
    setNewFilePermissions();
    changeWorkDirectory();
    closeAllOpenFiles();
}