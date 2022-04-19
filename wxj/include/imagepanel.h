#pragma once

#include <string>
#include <filesystem>
#include <optional>

#include "wx/wx.h"

namespace wxj
{
    class wxjImagePanel : public wxPanel
    {
    public:
        /**
         * @brief Construct a new image panel with an optional image as background
         * Note: Image will resize to parent size
         * @param parent
         * @param image
         */
        wxjImagePanel(wxFrame *parent, std::optional<std::filesystem::path> image);

        /**
         * @brief Force repaint
         */
        void paintNow();

    private:
        void paintEvent(wxPaintEvent &evt);
        void OnSize(wxSizeEvent &event);
        void render(wxDC &dc);

        std::optional<wxImage> m_image;
        wxBitmap m_resized;
        int m_w, m_h;

        DECLARE_EVENT_TABLE()
    };
}
