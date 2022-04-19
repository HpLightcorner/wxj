#include "imagepanel.h"
using namespace wxj;

BEGIN_EVENT_TABLE(wxj::wxjImagePanel, wxPanel)
EVT_PAINT(wxj::wxjImagePanel::paintEvent)
EVT_SIZE(wxj::wxjImagePanel::OnSize)
END_EVENT_TABLE()

wxjImagePanel::wxjImagePanel(wxFrame *parent, std::optional<std::filesystem::path> image) : wxPanel(parent)
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
}

void wxjImagePanel::paintEvent([[maybe_unused]] wxPaintEvent &evt)
{
    wxPaintDC dc(this);
    render(dc);
}

void wxjImagePanel::OnSize(wxSizeEvent &event)
{
    Refresh();
    event.Skip();
}

void wxjImagePanel::paintNow()
{
    wxClientDC dc(this);
    render(dc);
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
            dc.DrawBitmap(m_resized, 0, 0, false);
        }
    }
}
