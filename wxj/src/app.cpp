#include "app.h"
#include "imagepanel.h"
#include "button.h"
#include "config.h"
#include "dialogs.h"
#include "document.h"
#include "registry.h"

#include "wx/stdpaths.h"

using namespace wxj;

void wxj::registerDocument(Document::Pointer doc)
{
    auto &reg = DocumentRegistry::instance();
    reg.add(doc->getTag(), doc);
}

void wxj::unregisterDocument(Document::Pointer doc)
{
    auto &reg = DocumentRegistry::instance();
    reg.remove(doc->getTag());
}

bool App::OnInit()
{
    // Make sure App is using its current path as the working directory
    std::filesystem::path path(wxStandardPaths::Get().GetExecutablePath().ToStdString());
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
        style = wxNO_BORDER | wxCLIP_CHILDREN;
    }
    else
    {
        style = wxNO_BORDER | wxCLOSE_BOX | wxCAPTION | wxCLIP_CHILDREN;
    }

    // The Frame
    m_frame = new wxFrame(NULL, wxID_ANY, config.name, config.settings.pos, config.settings.size, style);
    m_frame->SetMinSize(config.settings.size);
    m_frame->SetMaxSize(config.settings.size);

    // Register wxj callbacks and expose them to config.json
    m_callbacks = std::make_shared<Callbacks>(m_frame);

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
