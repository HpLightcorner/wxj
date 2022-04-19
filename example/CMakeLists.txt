cmake_minimum_required(VERSION 3.20)
Include(FetchContent)

project(wxj-example)

#
# C++ Standard, Compiler Flags
set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} example.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE wxj)
