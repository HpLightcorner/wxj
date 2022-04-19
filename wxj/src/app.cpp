#include "app.h"
#include "imagepanel.h"
#include "button.h"
#include "config.h"
#include "dialogs.h"

#include "wx/stdpaths.h"

using namespace wxj;

void App::addFunction([[maybe_unused]] std::string tag, [[maybe_unused]] std::function<void()> func)
{
}

std::function<void()> App::addJsonDocument([[maybe_unused]] std::string tag, [[maybe_unused]] json *j)
{
    auto lambda = []() {

    };

    return lambda;
}

bool App::OnInit()
{
    std::filesystem::path path(wxStandardPaths::Get().GetExecutablePath());
    wxSetWorkingDirectory(path.parent_path().string());

    // Load app file
    auto c = fromFile("config.json");
    if (!c)
    {
        showErrorDialog("Loading config.json failed.");
        return false;
    }
    auto config = c.value();

    // let library user add functions
    if (!createApplication())
    {
        showErrorDialog("Creating Application failed.");
        return false;
    }

    // Enable Image support
    wxInitAllImageHandlers();

    // Options
    long style;
    if (config.settings.frameless)
    {
        style = wxFULLSCREEN_ALL;
    }
    else
    {
        style = wxCLOSE_BOX | wxCAPTION;
    }

    // The Frame
    m_frame = new wxFrame(NULL, wxID_ANY, config.name, config.settings.pos, config.settings.size, style);
    m_frame->SetMinSize(config.settings.size);
    m_frame->SetMaxSize(config.settings.size);

    // Add a custom image panel (background) using sizer
    auto sizer = new wxBoxSizer(wxHORIZONTAL);
    auto drawPane = new wxjImagePanel(m_frame, config.settings.bg);

    sizer->Add(drawPane, 1, wxEXPAND);
    m_frame->SetSizer(sizer);

    // add all elements to the pane
    for (const auto &[t, settings] : config.layout)
    {
        switch (t)
        {
        case Type::Button:
            new wxjButton(drawPane, std::get<wxjButton::Settings>(settings));
            break;
        case Type::Image:
            break;
        case Type::Text:
            break;
        }
    }

    // Finally, show the frame
    m_frame->Show(true);
    return true;
}
