#include "Messenger.hpp"

namespace Factory {
    void Messenger::printmessage(string& message) {
        string notificationMessage = " ==== For sale | Robot model: ";

        print(notificationMessage.append(message.c_str()));
    }
}
