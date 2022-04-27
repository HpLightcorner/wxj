#pragma once

#include <string>
#include <functional>
#include <optional>
#include <filesystem>

#include "types.h"
#include "document.h"
#include "binding.h"
#include "callbacks.h"

namespace wxj
{
    class App : public wxApp
    {
    public:
        struct Settings
        {
            Settings()
            {
                pos = wxDefaultPosition;
                size = wxDefaultSize;
                bg = std::nullopt;
                frameless = false;
            }

            Point pos;
            Size size;
            OptPath bg;
            bool frameless;
        };

        App();
        bool createFrame();
        bool resetFrame();
        wxFrame *getFrame();

    protected:
        /**
         * @brief Application Entry Point
         * Add all functions and json documents
         * @return true continue loading application
         * @return false abort
         */
        virtual bool createApplication() = 0;

    private:
        bool OnInit() final;
        wxFrame *m_frame;
        Bindings m_bindings;
        std::shared_ptr<Callbacks> m_callbacks;
    };
}

#define WXJ_IMPLEMENT_APP(app) wxIMPLEMENT_APP(app)
