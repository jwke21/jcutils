# Set minimum version of CMake required
cmake_minimum_required(VERSION 3.15)

# Set variable name This to name of project
set(This jcutils)

# Name of project and languages used
project(${This}
	LANGUAGES C
)

# Inform build system generator know which ver of C
set(CMAKE_C_STANDARD 11)

# https://cmake.org/cmake/help/latest/prop_tgt/POSITION_INDEPENDENT_CODE.html
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Copy Unity config file into ext/unity/download
configure_file(CMakeLists.txt.in ext/unity/download/CMakeLists.txt)

# CMake generate with Unity CMakeLists.txt
execute_process(COMMAND ${CMAKE_COMMAND} -G ${CMAKE_GENERATOR} .
	RESULT_VARIABLE result
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/ext/unity/download
)
if(result)
	message(FATAL_ERROR "CMake generate step for Unity failed: ${result}")
endif()
# CMake build with Unity CMakeLists.txt
execute_process(COMMAND ${CMAKE_COMMAND} --build .
	RESULT_VARIABLE result
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/ext/unity/download
)
if(result)
	message(FATAL_ERROR "Build step for Unity failed: ${result}")
endif()

# Add the Unity library
add_library(unity STATIC ${CMAKE_BINARY_DIR}/ext/unity/unity/src/unity.c)
# Add all directories to those searched by compiler for includes
include_directories(${CMAKE_BINARY_DIR}/ext/unity/unity/src src tests)
file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.c")
add_executable(This ${SOURCES})
target_include_directories(unity PUBLIC ${CMAKE_BINARY_DIR}/ext/unity/unity/src src)
target_link_libraries(This unity)

# Inform CMake that unit tests will be used
#enable_testing()

# Pull in dependencies
# add_subdirectory(googletest)

# Define Headers variable 
#set(Headers
#	jcutils_common.h
#	arraylist.h
#)
# Define Sources variable
#set(Sources
#	arraylist.c
#)

# Linked with other things to form programs
# Will compile the sources and make them into a library
#add_library(${This} STATIC ${Sources} ${Headers})

# Add the testing subdirectory
#add_subdirectory(test)

# Set the build directory
#set(CMAKE_BINARY_DIR ${PROJECT_SOURCE_DIR}/build)


