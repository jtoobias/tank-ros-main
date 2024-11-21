#include <SDL2/SDL.h>
#include <iostream>
#include <csignal>

bool sigInterrupt = true;

void signalHandler(int signum) {
    std::cout << "\nInterrupt signal (" << signum << ") received. Stopping...\n";
    sigInterrupt = false;
}

int main() {

    // Register signal handler
    std::signal(SIGINT, signalHandler);

    if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    if (SDL_NumJoysticks() < 1) {
        std::cerr << "No controllers connected!" << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_GameController* controller = SDL_GameControllerOpen(0);
    if (!controller) {
        std::cerr << "Failed to open controller: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Event event;
    while (sigInterrupt) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_CONTROLLERBUTTONDOWN) {
                std::cout << "Button pressed: " 
                          << (int)event.cbutton.button << std::endl;
            } else if (event.type == SDL_CONTROLLERBUTTONUP) {
                std::cout << "Button released: " 
                          << (int)event.cbutton.button << std::endl;
            } else if (event.type == SDL_CONTROLLERAXISMOTION) {
                switch (event.caxis.axis) {
                    case SDL_CONTROLLER_AXIS_LEFTX:
                        std::cout << "Left stick X: " << event.caxis.value << std::endl;
                        break;
                    case SDL_CONTROLLER_AXIS_LEFTY:
                        std::cout << "Left stick Y: " << event.caxis.value << std::endl;
                        break;
                    case SDL_CONTROLLER_AXIS_RIGHTX:
                        std::cout << "Right stick X: " << event.caxis.value << std::endl;
                        break;
                    case SDL_CONTROLLER_AXIS_RIGHTY:
                        std::cout << "Right stick Y: " << event.caxis.value << std::endl;
                        break;
                    case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
                        std::cout << "Left trigger: " << event.caxis.value << std::endl;
                        break;
                    case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
                        std::cout << "Right trigger: " << event.caxis.value << std::endl;
                        break;
                }
            }
        }
    }

    SDL_GameControllerClose(controller);
    SDL_Quit();
    return 0;
}