
#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "xbox_controller.hpp"
#include <chrono>
#include "string.h"

class ControllerNode : public rclcpp::Node
{
  public:
    ControllerNode(): Node("controller_node")
    {
      twist_publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", 10);

      timer_ = this->create_wall_timer(
            std::chrono::milliseconds((1/10)),  // Timer interval (20 Hz)
            std::bind(&ControllerNode::controller_update_callback, this)  // Timer callback function
        );
      // Declare parameters in C++ (with a namespace for controller)
      this->declare_parameter("/controller_node/remote_control.max_linear_speed", 0.5);  // Default value: 2.0
      this->declare_parameter("/controller_node/remote_control.max_angular_speed", 0.3);  // Default value: 0.5
      this->declare_parameter("/controller_node/remote_control.joy_stick_buffer", 1800);  // Default value: 2.0
      this->declare_parameter("/controller_node/remote_control.twist_frame_id", "base_link");  // Default value: 0.5
        // Declare the use_sim_time parameter if not already declared
      // this->declare_parameter("use_sim_time", true);

      // Get parameters with the namespace
      this->get_parameter("/controller_node/remote_control.max_linear_speed", max_linear_speed);
      this->get_parameter("/controller_node/remote_control.max_angular_speed", max_angular_speed);
      this->get_parameter("/controller_node/remote_control.joy_stick_buffer", joy_buffer);
      this->get_parameter("/controller_node/remote_control.twist_frame_id", frame_id);
    }

  private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr twist_publisher_;
    rclcpp::TimerBase::SharedPtr timer_;  // Timer object
    rclcpp::Clock::SharedPtr clock = std::make_shared<rclcpp::Clock>(RCL_SYSTEM_TIME);  // Or use RCL_ROS_TIME if you want ROS time

    Controller controller;
    // geometry_msgs::msg::Twist twist;

    int16_t joy_buffer;
    std::string frame_id;
    double max_linear_speed;     // Used for both directions
    double max_angular_speed;    // Used for both directions

    // Create function to handle
    geometry_msgs::msg::Twist controller_to_twist(void);
    void controller_update_callback(void);

    int16_t reverse_signed_int16(int16_t num) {
        if (num == -32768) {
            return 32767;  // Special case for -32768
        }
        return -num;
    }
};