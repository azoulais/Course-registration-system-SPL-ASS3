//
// Created by guy on 31/12/2020.
//

#include <iostream>
#include "Protocol.h"

Protocol::Protocol() : shouldTerminate(false), serverMessages({{12, "ACK"},
                                                                                                         {13, "ERROR"}}) {
}

bool Protocol::process(std::vector<short> &opcodeToProcess) {
    short command(opcodeToProcess[0]);
    short messageOpcode(opcodeToProcess[1]);
    switch (command) {
        case 12://ACK
            std::cout << serverMessages[command] << " " << messageOpcode << std::endl;
            return checkExtraInfo(messageOpcode);
        case 13://ERROR
            std::cout << serverMessages[command] << " " << messageOpcode << std::endl;
            switch (messageOpcode) {  //check if logout failed and
                case 4:
                    logoutConfirmation.set_value(false);
                    break;
            }
            break;
        default:
            break;
    }
    return false;
}

bool Protocol::getShouldTerminate() {
    return shouldTerminate;
}

bool Protocol::checkExtraInfo(short messageOpCode) {
    switch (messageOpCode) {
        case 4://logout
            shouldTerminate = true;
            logoutConfirmation.set_value(true);
            return false;
        case 6://kdamcheck
        case 7://coursestat
        case 8://studentstat
        case 9://isregistered
        case 11://mycoureses
            return true;
        default:
            return false;
    }
}

std::future<bool> Protocol::getLogoutFuture() {
    return logoutConfirmation.get_future();
}

void Protocol::setNewPromise() {
    logoutConfirmation = std::promise<bool>();
}
