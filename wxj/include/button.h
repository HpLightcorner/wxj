#pragma once

#include "types.h"

namespace wxj
{
    class wxjButton : public wxWindow
    {
    public:
        enum class State {
            Disabled,
            Current,
            Pressed,
            Default
        };

        struct Bg
        {
            Bg()
            {
                current = std::nullopt;
                pressed = std::nullopt;
                disabled = std::nullopt;
            }

            Path _default;
            OptPath current;
            OptPath pressed;
            OptPath disabled;
        };

        struct Settings
        {
            Settings()
            {
                bind = std::nullopt;
                label = std::nullopt;
                bg = std::nullopt;
            }

            OptString bind;
            OptString label;
            std::optional<Bg> bg;
            Point pos;
            Size size;
        };

        wxjButton(wxWindow *parent, Settings settings);
    
    protected:
        virtual void onButtonEvent();

    private:
        Settings m_settings;
        State m_state;

        std::optional<wxBitmap> m_default;
        std::optional<wxBitmap> m_current;
        std::optional<wxBitmap> m_pressed;
        std::optional<wxBitmap> m_disabled;

        void paintEvent(wxPaintEvent &evt);
        void paintNow();
        void render(wxDC &dc);

        void mouseEnterWindow(wxMouseEvent &event);
        void mouseDown(wxMouseEvent &event);
        void mouseReleased(wxMouseEvent &event);
        void mouseLeftWindow(wxMouseEvent &event);

        DECLARE_EVENT_TABLE()
    };
}
