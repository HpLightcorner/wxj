FetchContent_Declare(
    cpr 
    GIT_REPOSITORY https://github.com/libcpr/cpr.git
    GIT_TAG 1.8.1
) 

# Use system curl on OSX to make sure configs are correct
if(APPLE)
    set(CPR_FORCE_USE_SYSTEM_CURL ON)
endif()

FetchContent_MakeAvailable(cpr)
