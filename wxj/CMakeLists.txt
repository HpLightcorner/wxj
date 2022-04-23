cmake_minimum_required(VERSION 3.20)

#
# Include some helpers and the fetchcontent module for external dependencies
include(FetchContent)

#
# Define file-generate for relative paths
if(POLICY CMP0070)
   cmake_policy(SET CMP0070 NEW)
endif()

#
# Activate Policy for option() honors normal variables
if(POLICY CMP0077)
   cmake_policy(SET CMP0077 NEW)
   set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
endif()

#
# Project
project(wxj)

#
# C++ Standard, Compiler Flags
set(CMAKE_CXX_STANDARD 17)

if( MSVC )
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif()

#
# Sources
set(WXJGUI_HEADER_FILES
    include/app.h
    include/imagepanel.h
    include/config.h
    include/wxj.h
    include/button.h
    include/common.h
    include/dialogs.h
    include/registry.h
    include/observer.h
    include/document.h 
    include/binding.h
    include/callbacks.h
)
source_group("Header Files" FILES ${WXJGUI_HEADER_FILES})

set(WXJGUI_SOURCE_FILES
    src/imagepanel.cpp
    src/config.cpp
    src/app.cpp
    src/button.cpp
    src/dialogs.cpp
    src/label.cpp
    src/document.cpp
    src/callbacks.cpp
    src/binding.cpp
)
source_group("Source Files" FILES ${WXJGUI_SOURCE_FILES})


add_library(${PROJECT_NAME} STATIC
    ${WXJGUI_HEADER_FILES}
    ${WXJGUI_SOURCE_FILES}
)

#
# Set C++ Standard to 17
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

#
# Link Libraries 
target_link_libraries(${PROJECT_NAME} PUBLIC wxmono nlohmann_json fmt::fmt)

#
# Include Directories
target_include_directories(${PROJECT_NAME} PUBLIC include)
