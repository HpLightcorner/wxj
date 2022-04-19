#include "config.h"
#include <fstream>

void from_json(const nlohmann::json &j, wxSize &s)
{
    int width;
    int height;

    j.at("width").get_to(width);
    j.at("height").get_to(height);

    s.SetWidth(width);
    s.SetHeight(height);
}

void from_json(const nlohmann::json &j, wxPoint &p)
{
    j.at("x").get_to(p.x);
    j.at("y").get_to(p.y);
}

namespace wxj
{
    void from_json(const json &j, wxj::App::Settings &s)
    {
        if (j.contains("pos"))
        {
            s.pos = j.at("pos").get<wxj::Point>();
        }

        if (j.contains("size"))
        {
            s.size = j.at("size").get<wxj::Size>();
        }

        if (j.contains("bg"))
        {
            s.bg = j.at("bg").get<std::string>();
        }

        if (j.contains("frameless"))
        {
            s.frameless = j.at("frameless").get<bool>();
        }
    }

    void from_json(const json &j, wxjButton::Bg &bg)
    {
        bg._default = j.at("default").get<Path>();
        if (j.contains("current"))
        {
            bg.current = j.at("current").get<Path>();
        }
        if (j.contains("pressed"))
        {
            bg.pressed = j.at("pressed").get<Path>();
        }
        if (j.contains("disabled"))
        {
            bg.disabled = j.at("disabled").get<Path>();
        }
    }

    void from_json(const json &j, wxjButton::Settings &s)
    {
        if (j.contains("bind"))
        {
            s.bind = j.at("bind").get<std::string>();
        }
        if (j.contains("label"))
        {
            s.label = j.at("label").get<std::string>();
        }
        if (j.contains("bg"))
        {
            s.bg = j.at("bg").get<wxjButton::Bg>();
        }
        s.pos = j.at("pos").get<wxj::Point>();
        s.size = j.at("size").get<wxj::Size>();
    }

    void from_json(const json &j, Layout &l)
    {
        for (const auto &element : j)
        {
            if (element.contains("type"))
            {
                auto t = element.at("type").get<Type>();
                switch (t)
                {
                case Type::Button:
                {
                    auto b = element.get<wxjButton::Settings>();
                    l.push_back({Type::Button, b});
                }
                break;
                case Type::Image:
                    break;
                case Type::Text:
                    break;
                }
            }
        }
    }

    void from_json(const json &j, wxj::Config &c)
    {
        if (j.contains("name"))
        {
            j.at("name").get_to(c.name);
        }
        if (j.contains("settings"))
        {
            j.at("settings").get_to(c.settings);
        }
        if (j.contains("layout"))
        {
            j.at("layout").get_to(c.layout);
        }
    }
}

std::optional<wxj::Config> wxj::fromFile(std::filesystem::path path)
{
    if (std::filesystem::exists(path))
    {
        try
        {
            std::ifstream file(path);
            json j = json::parse(file);

            return j.get<Config>();
        }
        catch (...)
        {
            return std::nullopt;
        }
    }
    else
    {
        return std::nullopt;
    }
}