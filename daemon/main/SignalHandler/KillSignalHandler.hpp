#pragma once

#include <errno.h>
#include <signal.h>
#include <stdexcept>

#include "../Logging/Logger.hpp"

using std::runtime_error;

class KillSignalException : public runtime_error {
  public:
    KillSignalException(const std::string& _message) : std::runtime_error(_message) {
    }
};

class KillSignalHandler {
  private:
    string logtag = "KillSignalHandler";

  protected:
    static bool mbGotExitSignal;

  public:
    KillSignalHandler();
    ~KillSignalHandler();

    static bool isKillSignalReceived();
    static void setExitSignal(bool _bExitSignal);
    static void receiveSignal(int _ignored);
};