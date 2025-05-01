# CMakeLists.txt

cmake_minimum_required(VERSION 3.10)        # Specify minimum CMake version required

project(GMPBigNumTool VERSION 1.0 LANGUAGES CXX) # Define project name, version, and language (C++)

set(CMAKE_CXX_STANDARD 11)                  # Set the C++ standard to C++11 (or higher if needed)
set(CMAKE_CXX_STANDARD_REQUIRED True)       # Require the specified C++ standard

find_package(GMP REQUIRED)                  # Find the GMP library package, it's required for the build

include_directories(${GMP_INCLUDE_DIRS})    # Add GMP include directory to the project's include paths
include_directories(include)                # Add our own 'include' directory to the project's include paths

# Gather all source files from the src directory
file(GLOB SOURCES "src/*.cpp")              # Find all .cpp files in the src directory

add_executable(gmp_tool ${SOURCES})         # Create an executable named 'gmp_tool' from the source files

# Link the executable against the GMP library
target_link_libraries(gmp_tool PRIVATE ${GMP_LIBRARIES}) # Link gmp_tool with the found GMP libraries

# Optional: Add install rules if needed for packaging or system-wide installation
# install(TARGETS gmp_tool DESTINATION bin) # Example install rule
