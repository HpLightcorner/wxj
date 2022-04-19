#pragma once

#include <string>
#include <functional>
#include <optional>
#include <filesystem>

#include "types.h"

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

        /**
         * @brief Expose a function to the JSON settings file
         * @param tag
         * @param func
         */
        void addFunction(std::string tag, std::function<void()> func);

        /**
         * @brief Expose a json document to the JSON settings file
         * @param tag the tag to identify the document in the settings file
         * @param j pointer to use when accessing data
         * @return std::function<void()>
         */
        std::function<void()> addJsonDocument(std::string tag, json *j);

    private:
        bool OnInit() final;
        wxFrame *m_frame;
    };
}

#define WXJ_IMPLEMENT_APP(app) wxIMPLEMENT_APP(app)
