#pragma once
#include "types.h"
#include "observer.h"

namespace wxj
{
    class wxjLabel : public wxWindow, public IObserver<std::string>
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
        ~wxjLabel();

        void paintNow();

        void update(std::string tag) final;

    private:
        void paintEvent(wxPaintEvent &evt);
        void OnSize(wxSizeEvent &event);
        void render(wxDC &dc);

        Settings m_settings;
        DECLARE_EVENT_TABLE()
    };
}