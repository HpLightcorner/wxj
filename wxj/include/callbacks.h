#pragma once
#include "binding.h"
#include "types.h"

namespace wxj
{
    class Callbacks : public Binding
    {
    public:
        Callbacks(wxFrame *frame);
        void update(std::string tag) final;

    private:
        wxFrame *m_frame;
    };
}
