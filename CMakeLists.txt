cmake_minimum_required(VERSION 2.4)

project(lesson5
	LANGUAGES CXX)

add_executable(app main.cpp)

# tell CMake to use CTest extension
enable_testing()
add_subdirectory(googletest EXCLUDE_FROM_ALL)

# create an executable, which instantiates a runner from
# GoogleTest, Boost.Test, QtTest or whatever framework you use
add_executable(my_test
               test_main.cpp)

# depending on the framework, you need to link to it
target_link_libraries(my_test
                      gtest_main)

# now register the executable with CTest
add_test(NAME my_test COMMAND my_test)
