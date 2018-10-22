cmake_minimum_required(VERSION 3.12)
project(1_lab)

set(CMAKE_CXX_STANDARD 14)

#tests
add_subdirectory(lib/googletest-master)
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

add_executable(1_lab GTests/Tests.h GTests/test.cpp sources.cpp main.cpp)
target_link_libraries(1_lab gtest gtest_main)