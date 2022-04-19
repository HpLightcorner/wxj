#pragma once

#include "types.h"
#include "app.h"
#include "button.h"

#include <filesystem>
#include <memory>
#include <vector>
#include <variant>

namespace wxj
{
    using Settings = std::variant<wxjButton::Settings>;
    using Element = std::pair<Type, Settings>;
    using Layout = std::vector<Element>;

    struct Config {
        Config() {
            name = "wxJ";
        }

        std::string name;
        App::Settings settings;
        Layout layout;
    };

    std::optional<Config> fromFile(std::filesystem::path path);
}
