#include "KillSignalHandler.hpp"

bool KillSignalHandler::mbGotExitSignal = false;

KillSignalHandler::KillSignalHandler() {
    if (signal((int)SIGINT, KillSignalHandler::receiveSignal) == SIG_ERR) {
        throw KillSignalException("!!!!! Error setting up signal handlers !!!!!");
    }
}

KillSignalHandler::~KillSignalHandler() {
}

bool KillSignalHandler::isKillSignalReceived() {
    return mbGotExitSignal;
}

void KillSignalHandler::receiveSignal(int _ignored) {
    mbGotExitSignal = true;
}
