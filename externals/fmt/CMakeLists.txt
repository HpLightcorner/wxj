FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    USES_TERMINAL_DOWNLOAD TRUE
)


#
# Make sure FMT is build as a static library
set(BUILD_SHARED_LIBS OFF)

FetchContent_MakeAvailable(fmt)
set_property(TARGET fmt PROPERTY POSITION_INDEPENDENT_CODE ON)