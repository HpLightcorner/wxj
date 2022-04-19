#include "wxj.h"

class MyApp : public wxj::App
{
public:
    MyApp() : m_counter(0) {}

protected:
    bool createApplication() final
    {
        // We expose functions using a string-tag
        // The user can then bind events to these functions
        auto f1 = std::bind(&MyApp::increaseCounter, this);
        addFunction("increaseCounter", f1);

        auto f2 = std::bind(&MyApp::decreaseCounter, this);
        addFunction("decreaseCounter", f2);

        // When adding a json document, we get a function pointer in exchange
        // Whenever we change the json document, we can call the function pointer
        // to inform wxj to update any linked GUI elements
        m_update = addJsonDocument("data", &m_data);
        m_data["counter"] = m_counter;
        m_data["name"] = "My App";
        return true;
    }

private:
    void increaseCounter()
    {
        m_counter++;
        m_data["counter"] = m_counter;
        m_update();
    }
    void decreaseCounter()
    {
        m_counter--;
        m_data["counter"] = m_counter;
        m_update();
    }

    wxj::json m_data;
    int m_counter;
    wxj::Update m_update;
};

// Finally implement the app
WXJ_IMPLEMENT_APP(MyApp);