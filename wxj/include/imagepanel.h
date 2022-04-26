#pragma once

#include <string>
#include <filesystem>
#include <optional>

#include "wx/wx.h"
#include "wx/dcbuffer.h"

namespace wxj
{
    class wxjImagePanel : public wxPanel
    {
    public:
        wxjImagePanel(wxFrame *parent, std::optional<std::filesystem::path> image);

    private:
        void paintEvent(wxPaintEvent &evt);
        void onSize(wxSizeEvent &event);
        void render(wxDC &dc);

        std::optional<wxImage> m_image;
        wxBitmap m_resized;
        int m_w, m_h;

        DECLARE_EVENT_TABLE()
    };
}
