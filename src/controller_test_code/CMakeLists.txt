cmake_minimum_required(VERSION 3.10)  # You can adjust the version as needed
project(XboxControllerTest)

# Specify the C++ standard (optional but recommended)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the include directory to the compiler's search path
include_directories(~/ros2_ws/src/tank/include/tank)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

# Add all source files
set(SOURCES
    xbox_controller_test.cpp
    ../xbox_controller.cpp
)

# Create the executable from the source files
add_executable(xbox_controller_test ${SOURCES})

# Link libraries if necessary (e.g., SDL2, etc.)
target_link_libraries(xbox_controller_test ${SDL2_LIBRARIES})
