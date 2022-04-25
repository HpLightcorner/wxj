FetchContent_Declare(
    cpr 
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.6.1
) 

# Use system curl on OSX to make sure configs are correct
if(APPLE)
    set(CPR_FORCE_USE_SYSTEM_CURL ON)
endif()

#
# Make sure cpr is build as a static library
set(BUILD_SHARED_LIBS OFF)

FetchContent_MakeAvailable(cpr)
