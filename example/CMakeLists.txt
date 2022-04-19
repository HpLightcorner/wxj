cmake_minimum_required(VERSION 3.20)
Include(FetchContent)

project(wxj-example)

#
# C++ Standard, Compiler Flags
set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} example.cpp)

#
# Make sure to use WinMain on Windows
set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
target_link_libraries(${PROJECT_NAME} PRIVATE wxj)

#
# Build directly in example folder such that ressources can be found when debugging
set_target_properties(${PROJECT_NAME} PROPERTIES
                      RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR}
                      RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_SOURCE_DIR}
)
