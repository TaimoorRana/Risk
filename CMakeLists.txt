# Resources:
# * http://doc.qt.io/qt-5/cmake-manual.html
# * https://github.com/euler0/mini-cmake-qt

cmake_minimum_required(VERSION 3.0)

# Disable in-source builds (users must do a 'cd build/<your_platform>' first)
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
	message(FATAL_ERROR "In-source builds are not permitted. Change directory first and build in there:\ncd build/your_platform\nCMAKE_PREFIX_PATH=/path/to/qt5 cmake ../../\nBe sure to remove the 'CMakeCache.txt' and 'CMakeFiles' that were just created in the source tree first.")
endif("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")

# Add folder where are supportive functions
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Uncomment the next two lines for debugging
#include(debug)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Enable all compilation warnings
add_definitions( -Weverything )

# Basic info about project
project(risk VERSION 0.0.1)

# Set additional project information
set(COMPANY "COMP345")
set(COPYRIGHT "Copyright (c) 2015 COMP345 Team 1. All rights reserved.")
set(IDENTIFIER "github.taimoorrana1.risk")

# Process subdirectories
add_subdirectory(lib)
add_subdirectory(cli)
add_subdirectory(gui)
