cmake_minimum_required(VERSION 3.20)
Include(FetchContent)

project(top)

#
# Default: Disable Tests
option(BUILD_WITH_TESTS "Build with tests." OFF)
option(BUILD_WITH_SAMPLE "Build sample application." OFF)

if(BUILD_WITH_TESTS)
    # Ensure CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS is TRUE when Building with tests
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE)
endif()

add_subdirectory(externals)
add_subdirectory(wxj)

add_dependencies(wxj wxmono)
add_dependencies(wxj nlohmann_json)

if(BUILD_PLUGIN_WITH_TESTS)
    add_subdirectory(tests)
    add_dependencies(wxj-tests wxj)
endif()

if(BUILD_WITH_SAMPLE)
    add_subdirectory(example)
    add_dependencies(wxj-example wxj)
endif()
