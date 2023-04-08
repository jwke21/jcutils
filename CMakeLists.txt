# Set minimum version of CMake required
cmake_minimum_required(VERSION 3.15)

# Set variable name This to name of project
set(This jcutils)

# Name of project and languages used
project(${This} C)

# Inform build system generator know which ver of C
set(CMAKE_C_STANDARD 11)

# https://cmake.org/cmake/help/latest/prop_tgt/POSITION_INDEPENDENT_CODE.html
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Inform CMake that unit tests will be used
enable_testing()

# Pull in dependencies
# add_subdirectory(googletest)

# Define Headers variable 
set(Headers
	jcutils_common.h
	arraylist.h
)
# Define Sources variable
set(Sources
	arraylist.c
)

# Linked with other things to form programs
# Will compile the sources and make them into a library
add_library(${This} STATIC ${Sources} ${Headers})

add_subdirectory(test)



