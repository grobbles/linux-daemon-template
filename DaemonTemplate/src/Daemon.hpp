#pragma once

#include <algorithm>
#include <errno.h>
#include <fcntl.h>
#include <getopt.h>
#include <iostream>
#include <signal.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>
#include <unistd.h>
#include <vector>

using namespace std;

class Daemon {
  private:
    char* pid_file_name = NULL;
    int pid_fd = -1;

  public:
    Daemon();
    ~Daemon();

    void daemonize();
};