cmake_minimum_required(VERSION 3.10)  # Required CMake 3.10 or higher
project(GameFromScratch)  # Name of the project

# Set the C++ version
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the header directory
include_directories(include)

include_directories(lib)

# Find all source files in the src directory
file(GLOB SOURCES "src/*.cpp")

# Create the executable
add_executable(main ${SOURCES})

# Link the necessary libraries
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(main ${SDL2_LIBRARIES} SDL2_image)
