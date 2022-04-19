#include "label.h"
#include "fmt/core.h"
#include "fmt/format.h"
#include "fmt/args.h"

#include <unordered_set>
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
        auto &reg = ListenerRegistry::instance();
        std::unordered_set<std::string> tags;
        for (const auto &binding : m_settings.bindings.value())
        {
            tags.insert(binding.tag);
        }

        for (const auto &tag : tags)
        {
            reg.add(tag, this);
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
            auto t = reg.get(binding.tag);
            if (t)
            {
                auto d = t.value();
                auto ptr = json::json_pointer(binding.pointer);

                if (d->contains(ptr))
                {
                    auto v = d->at(ptr);

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
            }
        }
        label = fmt::vformat(label, args);
    }

    wxRect rect(m_settings.size);
    dc.DrawLabel(label, rect, wxALIGN_CENTER);
}

void wxjLabel::update()
{
    Refresh();
}
