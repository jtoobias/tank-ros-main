#include "controller_node.hpp"
#include <fenv.h>  // For enabling floating-point exceptions
    // Use this timer to check updates and publish data (can split later on if needed)
void ControllerNode::controller_update_callback(void){
        // Update all values from the controller
    controller.update_values();
    // std::cout << "Hih" << std::endl;
    geometry_msgs::msg::TwistStamped twist_stamped = controller_to_twiststamped();
    twist_publisher_->publish(twist_stamped);
}

    // Create function to handle
geometry_msgs::msg::TwistStamped ControllerNode::controller_to_twiststamped(void){
    geometry_msgs::msg::TwistStamped twist_stamped;
    int16_t joy_linear = controller.get_y_right_joy_value();
    int16_t joy_angular = reverse_signed_int16(controller.get_x_right_joy_value());
        // Convert right joy into throttle for linear and angular speeds
    if ((joy_linear >= joy_buffer) || (joy_linear <= -joy_buffer)){
			twist_stamped.twist.linear.x = (joy_linear/std::abs(joy_linear))*((double)(std::abs(joy_linear)-joy_buffer)/(JOY_AXIS_LIMIT-joy_buffer))*max_linear_speed;
    } else {
			twist_stamped.twist.linear.x = 0.0;
    }
        // Convert right joy into throttle for linear and angular speeds
    if ((joy_angular >= joy_buffer) || (joy_angular <= -joy_buffer)){
			twist_stamped.twist.angular.z = (joy_angular/std::abs(joy_angular))*(((double)std::abs(joy_angular)-joy_buffer)/(JOY_AXIS_LIMIT-joy_buffer))*max_angular_speed;
    } else {
			twist_stamped.twist.angular.z = 0.0;
    }
    twist_stamped.header.stamp = clock->now();
    twist_stamped.header.frame_id = frame_id;
    return twist_stamped;
}

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ControllerNode>());
  rclcpp::shutdown();
  return 0;
}