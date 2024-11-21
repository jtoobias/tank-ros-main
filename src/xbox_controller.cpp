#include "xbox_controller.hpp"
// Change code to be a library and not a main file
// create a controller class that has values for each button and joystick
// create an update function that will update values based on events. 
//  This function will need to be called by a main code consistently for frequent updates.


Controller::Controller (void){
    button_a = false;
    button_b = false;
    button_x = false;
    button_y = false;
    button_back = false;
    button_center = false;
    button_start = false;
    button_rbumper = false;
    button_lbumper = false;
    button_dpad_up = false;
    button_dpad_down = false;
    button_dpad_left = false;
    button_dpad_right = false;
    right_joy_x_value = 0;
    right_joy_y_value = 0;
    left_joy_x_value = 0;
    left_joy_y_value = 0;
    right_trigger_value = 0;
    left_trigger_value = 0;
    init_controller();
}

Controller::~Controller (void){
    remove_controller();
}

bool Controller::init_controller(void){
    if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    if (SDL_NumJoysticks() < 1) {
        std::cerr << "No controllers connected!" << std::endl;
        SDL_Quit();
        return false;
    }

    controller = SDL_GameControllerOpen(0);
    if (!controller) {
        std::cerr << "Failed to open controller: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    return true;
}

bool Controller::remove_controller(void){
    SDL_GameControllerClose(controller);
    SDL_Quit();
    return true;
}

    // Manage all events that are waiting in the queue
void Controller::update_values(void){
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
                    left_joy_x_value = event.caxis.value;
                    break;
                case SDL_CONTROLLER_AXIS_LEFTY:
                    std::cout << "Left stick Y: " << event.caxis.value << std::endl;
                    left_joy_y_value = event.caxis.value;
                    break;
                case SDL_CONTROLLER_AXIS_RIGHTX:
                    std::cout << "Right stick X: " << event.caxis.value << std::endl;
                    right_joy_x_value = event.caxis.value;
                    break;
                case SDL_CONTROLLER_AXIS_RIGHTY:
                    std::cout << "Right stick Y: " << event.caxis.value << std::endl;
                    right_joy_x_value = event.caxis.value;
                    break;
                case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
                    std::cout << "Left trigger: " << event.caxis.value << std::endl;
                    left_trigger_value = event.caxis.value;
                    break;
                case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
                    std::cout << "Right trigger: " << event.caxis.value << std::endl;
                    right_trigger_value = event.caxis.value;
                    break;
            }
        }
    }
}