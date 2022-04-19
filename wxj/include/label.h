#pragma once
#include "types.h"

namespace wxj
{
    class wxjLabel : public wxWindow, public Listener
    {
    public:
        struct Settings
        {
            Settings()
            {
                bindings = std::nullopt;
                label = "";
            }

            OptBindings bindings;
            std::string label;
            Point pos;
            Size size;
        };

        wxjLabel(wxWindow *parent, Settings settings);

        /**
         * @brief Force repaint
         */
        void paintNow();

        void update() final;

    private:
        void paintEvent(wxPaintEvent &evt);
        void OnSize(wxSizeEvent &event);
        void render(wxDC &dc);

        Settings m_settings;
        DECLARE_EVENT_TABLE()
    };
}