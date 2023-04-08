cmake_minimum_required(VERSION 3.15)

set(This jcutils_tests)

set(Sources
	arraylist_tests.c
)

# Makes the program
add_executable(${This} ${Sources})

# Pull in dependencies
target_link_libraries(${This} PUBLIC
	jcutils
)

# Include project source directory files
include_directories(
	${PROJECT_SOURCE_DIR}
)

# Inform CMake that this program is a unit test
add_test(
	NAME ${This}
	COMMAND ${This}
)

