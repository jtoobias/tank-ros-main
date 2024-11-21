#include "xbox_controller.hpp"
#include <csignal>

// Change code to be a library and not a main file
// create a controller class that has values for each button and joystick
// create an update function that will update values based on events. 
//  This function will need to be called by a main code consistently for frequent updates.

bool sigInterrupt = true;

void signalHandler(int signum) {
    std::cout << "\nInterrupt signal (" << signum << ") received. Stopping...\n";
    sigInterrupt = false;
}

int main() {

    // Register signal handler
    std::signal(SIGINT, signalHandler);
    Controller xbox; 
    while (sigInterrupt) {
        xbox.update_values();
    }
    return 0;
}