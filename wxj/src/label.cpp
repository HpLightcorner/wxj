#include "label.h"
#include "document.h"

#include "fmt/core.h"
#include "fmt/format.h"
#include "fmt/args.h"

using namespace wxj;

BEGIN_EVENT_TABLE(wxj::wxjLabel, wxPanel)
EVT_PAINT(wxjLabel::paintEvent)
EVT_SIZE(wxjLabel::OnSize)
END_EVENT_TABLE()

wxjLabel::wxjLabel(wxWindow *parent, Settings settings) : wxWindow(parent, wxID_ANY),
                                                          m_settings(settings)
{
    SetPosition(m_settings.pos);
    SetSize(m_settings.size);

    // Register as listener if documents of given tag change
    if (m_settings.bindings)
    {

        auto &reg = DocumentRegistry::instance();
        for (const auto &binding : m_settings.bindings.value())
        {
            // Get the document
            auto doc = reg.get(binding.tag);
            if (doc)
            {
                // Attach the label as an observer
                doc.value()->attach(this);
            }
        }
    }
}

wxjLabel::~wxjLabel()
{
    // Make sure to de-register the label from the document
    if (m_settings.bindings)
    {
        auto &reg = DocumentRegistry::instance();
        for (const auto &binding : m_settings.bindings.value())
        {
            auto doc = reg.get(binding.tag);
            if (doc)
            {
                doc.value()->detach(this);
            }
        }
    }
}

void wxjLabel::paintEvent([[maybe_unused]] wxPaintEvent &evt)
{
    wxPaintDC dc(this);
    render(dc);
}

void wxjLabel::OnSize(wxSizeEvent &event)
{
    Refresh();
    event.Skip();
}

void wxjLabel::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}

void wxjLabel::render(wxDC &dc)
{
    std::string label = m_settings.label;

    // Try to get bindings from documents
    if (m_settings.bindings)
    {
        auto &reg = DocumentRegistry::instance();
        fmt::dynamic_format_arg_store<fmt::format_context> args;

        for (const auto &binding : m_settings.bindings.value())
        {
            if (auto opt = reg.get(binding.tag))
            {
                auto doc = opt.value();

                // Lock the document while accessing underlying JSON
                doc->lock();
                auto json = doc->json();

                // Build a dynamic list of arguments for fmt
                auto ptr = Json::json_pointer(binding.pointer);

                if (json.contains(ptr))
                {
                    auto v = json.at(ptr);

                    // Limit Handling of JSON Data to supported formats
                    if (v.is_boolean())
                    {
                        args.push_back(v.get<bool>());
                    }
                    else if (v.is_number())
                    {
                        args.push_back(v.get<double>());
                    }
                    else if (v.is_string())
                    {
                        args.push_back(v.get<std::string>());
                    }
                }

                // Make sure to unlock
                doc->unlock();
            }
        }
        label = fmt::vformat(label, args);
    }

    wxRect rect(m_settings.size);
    dc.DrawLabel(label, rect, wxALIGN_CENTER);
}

void wxjLabel::update([[maybe_unused]] std::string tag)
{
    Refresh();
}
