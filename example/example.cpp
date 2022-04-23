#include <wxj.h>
#include <cpr/cpr.h>

#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

class MyData
{
public:
    MyData(std::string name)
    {
        setenv("CFNETWORK_DIAGNOSTICS", "3", 1);

        // Create a new document named data holding a JSON object to interact with the UI
        // Make sure that you are using a unique tag for each document
        m_doc = std::make_shared<wxj::Document>("data");
        auto &json = m_doc->json();
        json["bitcoin"]["usd"] = "NaN";
        json["timestamp"] = "Unknown";

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

    void setPrice(wxj::Json price, std::string timestamp)
    {
        // Lock for write access
        m_doc->lock();

        auto &json = m_doc->json();
        json = price;
        json["timestamp"] = timestamp;

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

    void updateBitcoinPrice()
    {
        auto r = cpr::Get(cpr::Url{"https://api.coingecko.com/api/v3/simple/price"},
                          cpr::Parameters{{"ids", "bitcoin"}, {"vs_currencies", "usd"}});

        if (r.status_code == 200)
        {
            auto t = std::time(nullptr);
            auto tm = *std::localtime(&t);

            std::ostringstream oss;
            oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
            auto timestamp = oss.str();

            m_data.setPrice(wxj::Json::parse(r.text), timestamp);
        }
    }

    void update(std::string tag) final
    {
        if (tag == "refresh")
        {
            updateBitcoinPrice();
        }
    }

protected:
    bool createApplication() final
    {
        // We expose functions using a string-tag
        // Be careful that register binding stores a pointer to the binding
        // If you delete the binding (e.g. this class) at runtime, make sure to unregister first
        // Use unique identifiers
        wxj::registerBinding("refresh", this);

        // Set initial value
        updateBitcoinPrice();
        return true;
    }

private:
    MyData m_data;
};

// Finally implement the app
WXJ_IMPLEMENT_APP(MyApp);