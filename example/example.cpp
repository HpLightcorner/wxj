#include "wxj.h"

class MyApp : public wxj::App, wxj::Binding
{
public:
    MyApp() : m_counter(0) {}

    void update(std::string tag) final
    {
        // Lock the document while editing
        m_data->lock();

        // Convinient JSON-Access
        auto &json = m_data->json();

        if (tag == "increaseCounter")
        {
            m_counter++;
        }
        if (tag == "decreaseCounter")
        {
            m_counter--;
        }
        json["counter"] = m_counter;

        // Unlock document
        m_data->unlock();

        // Notify wxj about changes made in the document
        m_data->notify();
    }

protected:
    bool createApplication() final
    {
        // We expose functions using a string-tag
        // Be careful that register binding stores a pointer to the binding
        // If you delete the binding (e.g. this class) at runtime, make sure to unregister first
        // Use unique identifiers
        wxj::registerBinding("increaseCounter", this);
        wxj::registerBinding("decreaseCounter", this);

        // Create a new document named data holding a JSON object to interact with the UI
        // Make sure that you are using a unique tag for each document
        m_data = std::make_shared<wxj::Document>("data");

        // Register the Document within wxj such that the document can be accessed from the
        // config document. Be careful, registerDocument takes ownership of the document!
        wxj::registerDocument(m_data);

        auto &json = m_data->json();
        json["counter"] = m_counter;
        json["name"] = "My App";

        return true;
    }

private:
    wxj::Document::Pointer m_data;
    int m_counter;
};

// Finally implement the app
WXJ_IMPLEMENT_APP(MyApp);