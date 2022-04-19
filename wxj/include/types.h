#pragma once
#include "wx/wx.h"
#include "nlohmann/json.hpp"

#include <optional>
#include <string>
#include <filesystem>

#include "registry.h"
#include "listener.h"

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
    using Update = std::function<void()>;

    using FunctionRegistry = Registry<std::function<void()>>;
    using DocumentRegistry = Registry<json *>;
    using ListenerRegistry = MultiRegistry<Listener *>;

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

    NLOHMANN_JSON_SERIALIZE_ENUM(Type, {{Type::Button, "button"},
                                        {Type::Image, "image"},
                                        {Type::Label, "label"}})
}
