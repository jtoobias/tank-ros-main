cmake_minimum_required(VERSION 3.8)
project(tank)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(controller_node src/controller_node.cpp src/xbox_controller.cpp)
ament_target_dependencies(controller_node rclcpp std_msgs geometry_msgs)

# Add the include directory to the compiler's search path
target_include_directories(controller_node PRIVATE include/tank)
# Link libraries if necessary (e.g., SDL2, etc.)
target_link_libraries(controller_node ${SDL2_LIBRARIES})

# Install the controller_node executable
install(TARGETS controller_node
  DESTINATION lib/${PROJECT_NAME}
)

# Install directories (config, params, description, etc.)
install(DIRECTORY config/ params/ description/ launch/ worlds/
  DESTINATION share/${PROJECT_NAME}
)



if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
