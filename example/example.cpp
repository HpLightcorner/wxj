#include "wxj.h"

class MyData
{
public:
    MyData(std::string name)
    {
        // Create a new document named data holding a JSON object to interact with the UI
        // Make sure that you are using a unique tag for each document
        m_doc = std::make_shared<wxj::Document>("data");
        auto &json = m_doc->json();
        json["name"] = name;
        json["counter"] = 0;
        json["cs2"] = 11;

        // Register the Document within wxj such that the document can be accessed from the
        // config document. Be careful, registerDocument takes ownership of the document!
        wxj::registerDocument(m_doc);
    }

    ~MyData()
    {
        // Make sure to drop ownership when deleting the document
        wxj::unregisterDocument(m_doc);
        m_doc.reset();
    }

    int getCounter()
    {
        auto &json = m_doc->json();
        return json["counter"].get<int>();
    }

    void setCounter(int counter)
    {
        // Lock for write access
        m_doc->lock();

        auto &json = m_doc->json();
        json["counter"] = counter;

        // Unlock before notify
        m_doc->unlock();

        // Notify all observers about changes in the document
        m_doc->notify();
    }

private:
    wxj::Document::Pointer m_doc;
    int m_counter;
};

class MyApp : public wxj::App,
              public wxj::Binding
{
public:
    MyApp() : m_data("My App")
    {
    }

    void update(std::string tag) final
    {
        auto counter = m_data.getCounter();
        if (tag == "increaseCounter")
        {
            counter++;
        }
        if (tag == "decreaseCounter")
        {
            counter--;
        }
        m_data.setCounter(counter);
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
        return true;
    }

private:
    MyData m_data;
};

// Finally implement the app
WXJ_IMPLEMENT_APP(MyApp);