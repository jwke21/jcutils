cmake_minimum_required(VERSION 3.14)

set(This jcutils_tests)

set(Sources
	jcutils_tests.c
)

# Makes the program
add_executable(${This} ${Sources})
# Pull in dependencies
target_linked_libraries(${This} PUBLIC
	gtest_main
	jcutils
)
# Inform CMake that this program is a unit test
add_test(
	NAME ${This}
	COMMAND ${This}
)

