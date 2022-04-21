#pragma once
#include "wx/wx.h"
#include "nlohmann/json.hpp"

#include <optional>
#include <string>
#include <filesystem>

namespace wxj
{
    // JSON (Documents)
    using Json = nlohmann::json;
    using JsonSharedPtr = std::shared_ptr<Json>;
    using JsonWeakPtr = std::weak_ptr<Json>;

    // UI and config document
    using Point = wxPoint;
    using Size = wxSize;
    using OptPoint = std::optional<Point>;
    using OptSize = std::optional<Size>;

    enum class Type
    {
        Button,
        Label,
        Image
    };

    struct Bind
    {
        std::string tag;
        std::string pointer;
    };

    using OptBind = std::optional<Bind>;
    using Bindings = std::vector<Bind>;
    using OptBindings = std::optional<Bindings>;

    // Paths
    using Path = std::filesystem::path;
    using OptPath = std::optional<Path>;

    // Strings
    using String = std::string;
    using OptString = std::optional<String>;
}
