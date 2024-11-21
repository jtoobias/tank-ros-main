#include <iostream>
#include <SDL2/SDL.h>
#include <limits.h>

constexpr uint8_t BUTTON_A_NUM = 0; 
constexpr uint8_t BUTTON_B_NUM = 1; 
constexpr uint8_t BUTTON_X_NUM = 2; 
constexpr uint8_t BUTTON_Y_NUM = 3; 
constexpr uint8_t BUTTON_BACK_NUM = 4; 
constexpr uint8_t BUTTON_CENTER_NUM = 5; 
constexpr uint8_t BUTTON_START_NUM = 6; 
constexpr uint8_t BUTTON_LEFT_JOY_NUM = 7; 
constexpr uint8_t BUTTON_RIGHT_JOY_NUM = 8;
constexpr uint8_t BUTTON_LEFT_BUMPER_NUM = 9; 
constexpr uint8_t BUTTON_RIGHT_BUMPER_NUM = 10;
constexpr uint8_t BUTTON_DPAD_UP_NUM = 11; 
constexpr uint8_t BUTTON_DPAD_DOWN_NUM = 12; 
constexpr uint8_t BUTTON_DPAD_LEFT_NUM = 13; 
constexpr uint8_t BUTTON_DPAD_RIGHT_NUM = 14; 


constexpr int16_t JOY_AXIS_LIMIT = std::numeric_limits<int16_t>::max();
constexpr int16_t TRIGGER_LIMIT = std::numeric_limits<int16_t>::max();

class Controller
{
    public:
        // Functions
        Controller();
        ~Controller();

        bool init_controller(void);
        bool remove_controller(void);
        void update_values(void);

            // Protect variables from being set externally, with getter functions
        bool is_button_A_pressed() const { return button_a; } // Does not modify `button_a`
        bool is_button_B_pressed() const { return button_b; }
        bool is_button_X_pressed() const { return button_x; }
        bool is_button_Y_pressed() const { return button_y; }

        bool is_button_right_bumper_pressed() const  { return button_rbumper; } 
        bool is_button_left_bumper_pressed() const { return button_lbumper; }

        bool is_button_center_pressed() const { return button_center; }
        bool is_button_start_pressed() const { return button_start; }

        bool is_dpad_up_pressed()  const   { return button_dpad_up; }
        bool is_dpad_down_pressed() const  { return button_dpad_down; }
        bool is_dpad_right_pressed() const { return button_dpad_right; }
        bool is_dpad_left_pressed() const  { return button_dpad_left; }
        bool is_joy_right_pressed() const { return button_right_joy; }
        bool is_joy_left_pressed() const  { return button_left_joy; }

        int16_t get_x_right_joy_value()  const   { return right_joy_x_value; }
        int16_t get_y_right_joy_value()  const   { return right_joy_y_value; }
        int16_t get_x_left_joy_value() const  { return left_joy_x_value; }
        int16_t get_y_left_joy_value() const  { return left_joy_y_value; }
        int16_t get_right_trigger_value() const { return right_trigger_value; }
        int16_t get_left_trigger_value() const  { return left_trigger_value; }


    private:

        SDL_Event event;
        SDL_GameController* controller_ptr;
        // Variables for each button
        bool button_a;
        bool button_b;
        bool button_x;
        bool button_y;
        bool button_back;
        bool button_center;
        bool button_start;
        bool button_rbumper;
        bool button_lbumper;
        bool button_dpad_up;
        bool button_dpad_down;
        bool button_dpad_left;
        bool button_dpad_right;
        bool button_left_joy;
        bool button_right_joy;

        int16_t right_joy_x_value;
        int16_t right_joy_y_value;
        int16_t left_joy_x_value;
        int16_t left_joy_y_value;

        int16_t right_trigger_value;
        int16_t left_trigger_value;

        int16_t reverse_sign(int16_t num) {
            if (num == -32768) {
                return 32767;  // Special case for -32768
            }
            return -num;
        }
};
