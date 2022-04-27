#include "callbacks.h"
#include "app.h"
using namespace wxj;

Callbacks::Callbacks(App *app) : m_app(app)
{
    wxj::registerBinding("$close", this);
    wxj::registerBinding("$reload", this);
}

void Callbacks::update(std::string tag)
{
    if (tag == "$close")
    {
        m_app->getFrame()->Close(true);
    }
    else if (tag == "$reload")
    {
        m_app->resetFrame();
    }
}
