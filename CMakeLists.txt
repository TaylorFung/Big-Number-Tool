cmake_minimum_required(VERSION 3.10)
project(GMPBigNumTool VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Option 1: Try modern find_package first (if GMP provides a config file)
find_package(GMP QUIET)

# Option 2: Fall back to manual detection if find_package fails
if(NOT GMP_FOUND)
    find_path(GMP_INCLUDE_DIR NAMES gmp.h)
    find_library(GMP_LIBRARY NAMES gmp)
    find_library(GMPXX_LIBRARY NAMES gmpxx)  # Needed if using C++ bindings

    if(GMP_INCLUDE_DIR AND GMP_LIBRARY)
        set(GMP_FOUND TRUE)
        set(GMP_INCLUDE_DIRS ${GMP_INCLUDE_DIR})
        set(GMP_LIBRARIES ${GMP_LIBRARY})
        if(GMPXX_LIBRARY)
            list(APPEND GMP_LIBRARIES ${GMPXX_LIBRARY})
        endif()
    endif()
endif()

# Fail if GMP not found
if(NOT GMP_FOUND)
    message(FATAL_ERROR "GMP library not found. Install libgmp-dev (Linux) or gmp (macOS).")
endif()

include_directories(${GMP_INCLUDE_DIRS})
include_directories(include)

file(GLOB SOURCES "src/*.cpp")
add_executable(gmp_tool ${SOURCES})

target_link_libraries(gmp_tool PRIVATE ${GMP_LIBRARIES})

# Optional: Better to list sources explicitly instead of GLOB
# set(SOURCES src/main.cpp src/other.cpp)
