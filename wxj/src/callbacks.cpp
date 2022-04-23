#include "callbacks.h"
using namespace wxj;

Callbacks::Callbacks(wxFrame *frame) : m_frame(frame)
{
    wxj::registerBinding("$close", this);
}

void Callbacks::update(std::string tag)
{
    if (tag == "$close")
    {
        m_frame->Close(true);
    }
}
