# Resources:
# * http://doc.qt.io/qt-5/cmake-manual.html
# * https://github.com/euler0/mini-cmake-qt


set(CMAKE_OSX_DEPLOYMENT_TARGET, 10.10)
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)

# Disable in-source builds (users must do a 'cd build/<your_platform>' first)
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
	message(FATAL_ERROR "In-source builds are not permitted. Change directory first and build in there:\ncd build/your_platform\nCMAKE_PREFIX_PATH=/path/to/qt5 cmake ../../\nBe sure to remove the 'CMakeCache.txt' and 'CMakeFiles' that were just created in the source tree first.")
endif("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")

# Add folder where are supportive functions
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Uncomment the next two lines for debugging
#include(debug)

find_package(Doxygen)
if(DOXYGEN_FOUND)
	configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
	add_custom_target(doc
		${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation with Doxygen" VERBATIM
	)
endif(DOXYGEN_FOUND)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

IF (APPLE)
	# Enable all compilation warnings
	add_definitions( -Wall )
ENDIF (APPLE)

# Basic info about project
project(risk VERSION 0.0.1)

# Set additional project information
set(COMPANY "COMP345")
set(COPYRIGHT "Copyright (c) 2015 COMP345 Team 1. All rights reserved.")
set(IDENTIFIER "github.taimoorrana1.risk")

# Process subdirectories
add_subdirectory(lib)
add_subdirectory(gui)
