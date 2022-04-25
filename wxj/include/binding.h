#pragma once

#include "observer.h"
#include "registry.h"

#include <memory>
#include <string>

namespace wxj
{
    using Binding = IObserver<std::string>;
    using Glue = Subject<std::string, 1>;
    using BindingRegistry = Registry<std::shared_ptr<Glue>>;

    void registerBinding(std::string tag, Binding::WeakPointer b);
}
