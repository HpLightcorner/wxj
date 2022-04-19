#pragma once
#include "wx/wx.h"
#include "nlohmann/json.hpp"

#include <optional>
#include <string>
#include <filesystem>

namespace wxj
{
    using nlohmann::json;
    using Point = wxPoint;
    using Size = wxSize;
    using OptPoint = std::optional<Point>;
    using OptSize = std::optional<Size>;
    using OptString = std::optional<std::string>;
    using Path = std::filesystem::path;
    using OptPath = std::optional<Path>;

    enum class Type
    {
        Button,
        Text,
        Image
    };

    NLOHMANN_JSON_SERIALIZE_ENUM(Type, {{Type::Button, "button"},
                                        {Type::Image, "image"},
                                        {Type::Text, "text"}})
}
