FetchContent_Declare(
    wxWidgets
    GIT_REPOSITORY https://github.com/wxWidgets/wxWidgets.git
    GIT_TAG        v3.1.6
)

set(wxUSE_STL ON)
set(wxBUILD_MONOLITHIC ON)
set(wxBUILD_SHARED OFF)
FetchContent_MakeAvailable(wxWidgets)
