#pragma once

#include <string>
#include <functional>
#include <optional>
#include <filesystem>

#include "types.h"
#include "document.h"
#include "binding.h"

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
    };

    void registerDocument(Document::Pointer doc);
    void registerBinding(std::string tag, Binding::WeakPointer b);
    void unregisterDocument(Document::Pointer doc);
}

#define WXJ_IMPLEMENT_APP(app) wxIMPLEMENT_APP(app)
