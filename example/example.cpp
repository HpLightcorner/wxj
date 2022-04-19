#include "wxj.h"

class MyApp : public wxj::App
{
public:
    MyApp() = default;

protected:
    bool createApplication() final
    {

        // We expose functions using a string-tag
        // The user can then bind events to these functions
        auto f = std::bind(&MyApp::onLoadSettings, this);
        addFunction("onLoadSettings", f);

        // When adding a json document, we get a function pointer in exchange
        // Whenever we change the json document, we can call the function pointer
        // to inform wxj to update any linked GUI elements
        auto on_update = addJsonDocument("data", &m_data);
        return true;
    }

private:
    void onLoadSettings()
    {
    }

    wxj::json m_data;
};

// Finally implement the app
WXJ_IMPLEMENT_APP(MyApp);