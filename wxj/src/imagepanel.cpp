#include "imagepanel.h"
using namespace wxj;

BEGIN_EVENT_TABLE(wxjImagePanel, wxPanel)
EVT_PAINT(wxjImagePanel::paintEvent)
EVT_SIZE(wxjImagePanel::onSize)
END_EVENT_TABLE()

wxjImagePanel::wxjImagePanel(wxFrame *parent, std::optional<std::filesystem::path> image) : wxPanel()
{
    if (image)
    {
        auto p = image.value();
        if (std::filesystem::exists(p))
        {
            m_image = wxImage(p.string());
        }
    }

    m_w = -1;
    m_h = -1;

    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Create(parent, wxID_ANY);

    // Make sure to double-buffer (for Windows)
    SetDoubleBuffered(true);
}

void wxjImagePanel::paintEvent([[maybe_unused]] wxPaintEvent &evt)
{
    wxPaintDC dc(this);
    render(dc);
}

void wxjImagePanel::onSize([[maybe_unused]] wxSizeEvent &event)
{
    Refresh();
    event.Skip();
}

void wxjImagePanel::render(wxDC &dc)
{
    if (m_image)
    {
        int neww, newh;
        dc.GetSize(&neww, &newh);

        if (neww != m_w || newh != m_h)
        {
            m_resized = wxBitmap(m_image.value().Scale(neww, newh /*, wxIMAGE_QUALITY_HIGH*/));
            m_w = neww;
            m_h = newh;
            dc.DrawBitmap(m_resized, 0, 0, false);
        }
        else
        {
            auto region = GetUpdateRegion();
            if (region.IsOk())
            {
                auto rect = region.GetBox();
                auto submap = m_resized.GetSubBitmap(rect);
                dc.DrawBitmap(submap, rect.GetTopLeft());
            }
            else
            {
                dc.DrawBitmap(m_resized, 0, 0, false);
            }
        }
    }
}
