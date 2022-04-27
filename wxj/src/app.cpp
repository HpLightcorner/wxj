#include "app.h"
#include "imagepanel.h"
#include "button.h"
#include "config.h"
#include "dialogs.h"
#include "document.h"
#include "registry.h"

#include "wx/stdpaths.h"

using namespace wxj;

App::App() : m_frame(nullptr)
{
}

bool App::createFrame()
{
    // Load app file
    auto c = fromFile("config.json");
    if (!c)
    {
        showErrorDialog("Loading config.json failed.");
        return false;
    }
    auto config = c.value();

    // Options
    long style;
    if (config.settings.frameless)
    {
        style = wxNO_BORDER | wxCLIP_CHILDREN;
    }
    else
    {
        style = wxNO_BORDER | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN;
    }

    // The Frame
    m_frame = new wxFrame(NULL, wxID_ANY, config.name, config.settings.pos, config.settings.size, style);
    m_frame->SetClientSize(config.settings.size);

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
        case Type::Label:
            new wxjLabel(drawPane, std::get<wxjLabel::Settings>(settings));
            break;
        }
    }

    // Finally, show the frame
    m_frame->Show(true);

    // Make Sure to (re)size
    m_frame->SendSizeEvent();

    return true;
}

wxFrame* App::getFrame()
{
    return m_frame;
}

bool App::resetFrame()
{
    // Destroy frame if exists, then create from file
    if (m_frame)
    {
        m_frame->Destroy();
        m_frame = nullptr;

        return createFrame();
    }
    else
    {
        throw std::runtime_error("Frame must exist to reset.");
    }
}

bool App::OnInit()
{
    // Make sure App is using its current path as the working directory
    std::filesystem::path path(wxStandardPaths::Get().GetExecutablePath().ToStdString());
    wxSetWorkingDirectory(path.parent_path().string());

    // let user add functions
    if (!createApplication())
    {
        showErrorDialog("Creating Application failed.");
        return false;
    }

    // Enable Image support
    wxInitAllImageHandlers();

    // Register wxj callbacks and expose them to config.json
    m_callbacks = std::make_shared<Callbacks>(this);

    // Finally, create the frame
    return createFrame();
}
