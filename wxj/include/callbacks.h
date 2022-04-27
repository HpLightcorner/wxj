#pragma once
#include "binding.h"
#include "types.h"

namespace wxj
{
    class App;
    class Callbacks : public Binding
    {
    public:
        Callbacks(App *app);
        void update(std::string tag) final;

    private:
        App *m_app;
    };
}
