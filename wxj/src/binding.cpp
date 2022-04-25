#include "binding.h"
using namespace wxj;

void wxj::registerBinding(std::string tag, Binding::WeakPointer b)
{
    auto &reg = BindingRegistry::instance();
    auto glue = std::make_shared<Glue>();
    glue->attach(b);

    reg.add(tag, glue);
}
