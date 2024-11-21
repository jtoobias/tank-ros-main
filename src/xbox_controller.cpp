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

    controller_ptr = SDL_GameControllerOpen(0);
    if (!controller_ptr) {
        std::cerr << "Failed to open controller: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }
    return true;
}

bool Controller::remove_controller(void){
    SDL_GameControllerClose(controller_ptr);
    SDL_Quit();
    return true;
}

    // Manage all events that are waiting in the queue
void Controller::update_values(void){
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_CONTROLLERBUTTONDOWN) {
            switch (event.cbutton.button){
                case BUTTON_A_NUM:
                    button_a = true;
                    break;
                case BUTTON_B_NUM:
                    button_b = true;
                    break;
                case BUTTON_X_NUM:
                    button_x = true;
                    break;
                case BUTTON_Y_NUM:
                    button_y = true;
                    break;
                case BUTTON_BACK_NUM:
                    button_back = true;
                    break;
                case BUTTON_CENTER_NUM:
                    button_center = true;
                    break;
                case BUTTON_START_NUM:
                    button_start = true;
                    break;
                case BUTTON_LEFT_JOY_NUM:
                    button_left_joy = true;
                    break;
                case BUTTON_RIGHT_JOY_NUM:
                    button_right_joy = true;
                    break;
                case BUTTON_LEFT_BUMPER_NUM:
                    button_lbumper = true;
                    break;
                case BUTTON_RIGHT_BUMPER_NUM:
                    button_rbumper = true;
                    break;
                case BUTTON_DPAD_UP_NUM:
                    button_dpad_up = true;
                    break;
                case BUTTON_DPAD_DOWN_NUM:
                    button_dpad_down = true;
                    break;
                case BUTTON_DPAD_LEFT_NUM:
                    button_dpad_left = true;
                    break;
                case BUTTON_DPAD_RIGHT_NUM:
                    button_dpad_right = true;
                    break;
            }
        } else if (event.type == SDL_CONTROLLERBUTTONUP) {
            switch (event.cbutton.button){
                case BUTTON_A_NUM:
                    button_a = false;
                    break;
                case BUTTON_B_NUM:
                    button_b = false;
                    break;
                case BUTTON_X_NUM:
                    button_x = false;
                    break;
                case BUTTON_Y_NUM:
                    button_y = false;
                    break;
                case BUTTON_BACK_NUM:
                    button_back = false;
                    break;
                case BUTTON_CENTER_NUM:
                    button_center = false;
                    break;
                case BUTTON_START_NUM:
                    button_start = false;
                    break;
                case BUTTON_LEFT_JOY_NUM:
                    button_left_joy = false;
                    break;
                case BUTTON_RIGHT_JOY_NUM:
                    button_right_joy = false;
                    break;
                case BUTTON_LEFT_BUMPER_NUM:
                    button_lbumper = false;
                    break;
                case BUTTON_RIGHT_BUMPER_NUM:
                    button_rbumper = false;
                    break;
                case BUTTON_DPAD_UP_NUM:
                    button_dpad_up = false;
                    break;
                case BUTTON_DPAD_DOWN_NUM:
                    button_dpad_down = false;
                    break;
                case BUTTON_DPAD_LEFT_NUM:
                    button_dpad_left = false;
                    break;
                case BUTTON_DPAD_RIGHT_NUM:
                    button_dpad_right = false;
                    break;
            }
        } else if (event.type == SDL_CONTROLLERAXISMOTION) {
            switch (event.caxis.axis) {
                case SDL_CONTROLLER_AXIS_LEFTX:
                    left_joy_x_value = event.caxis.value;
                    break;
                case SDL_CONTROLLER_AXIS_LEFTY:
                    left_joy_y_value = reverse_sign(event.caxis.value);
                    break;
                case SDL_CONTROLLER_AXIS_RIGHTX:
                    right_joy_x_value = event.caxis.value;
                    break;
                case SDL_CONTROLLER_AXIS_RIGHTY:
                    right_joy_y_value = reverse_sign(event.caxis.value);
                    break;
                case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
                    left_trigger_value = event.caxis.value;
                    break;
                case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
                    right_trigger_value = event.caxis.value;
                    break;
            }
        }
    }
}