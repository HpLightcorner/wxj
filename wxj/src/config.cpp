#include "config.h"
#include <fstream>

void from_json(const wxj::Json &j, wxSize &s)
{
    int width;
    int height;

    j.at("width").get_to(width);
    j.at("height").get_to(height);

    s.SetWidth(width);
    s.SetHeight(height);
}

void from_json(const wxj::Json &j, wxPoint &p)
{
    j.at("x").get_to(p.x);
    j.at("y").get_to(p.y);
}

namespace wxj
{
    NLOHMANN_JSON_SERIALIZE_ENUM(Type, {{Type::Button, "button"},
                                        {Type::Image, "image"},
                                        {Type::Label, "label"}})

    NLOHMANN_JSON_SERIALIZE_ENUM(Align, {{Align::Left, "left"},
                                         {Align::Center, "center"},
                                         {Align::Right, "right"}})

    NLOHMANN_JSON_SERIALIZE_ENUM(Color, {{Color::Black, "black"},
                                         {Color::White, "white"}})

    void from_json(const Json &j, wxj::Bind &b)
    {
        j.at("tag").get_to(b.tag);
        j.at("pointer").get_to(b.pointer);
    }

    void from_json(const Json &j, wxj::Bindings &b)
    {
        for (const auto &entry : j)
        {
            auto bind = entry.get<wxj::Bind>();
            b.push_back(bind);
        }
    }

    void from_json(const Json &j, wxj::App::Settings &s)
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

    void from_json(const Json &j, wxjButton::Bg &bg)
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

    void from_json(const Json &j, wxjButton::Settings &s)
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

    void from_json(const Json &j, Font &f)
    {
        if (j.contains("facename"))
        {
            f.facename = j.at("facename").get<std::string>();
        }
        if (j.contains("height"))
        {
            f.height = j.at("height").get<int>();
        }
        if (j.contains("align"))
        {
            f.align = j.at("align").get<Align>();
        }
        if (j.contains("color"))
        {
            f.color = j.at("color").get<Color>();
        }
    }

    void from_json(const Json &j, wxjLabel::Settings &s)
    {
        if (j.contains("bindings"))
        {
            s.bindings = j.at("bindings").get<wxj::Bindings>();
        }
        if (j.contains("font"))
        {
            s.font = j.at("font").get<wxj::Font>();
        }
        s.label = j.at("label");
        s.pos = j.at("pos").get<wxj::Point>();
        s.size = j.at("size").get<wxj::Size>();
    }

    void from_json(const Json &j, Layout &l)
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
                    auto s = element.get<wxjButton::Settings>();
                    l.push_back({Type::Button, s});
                }
                break;
                case Type::Image:
                    break;
                case Type::Label:
                {
                    auto s = element.get<wxjLabel::Settings>();
                    l.push_back({Type::Label, s});
                }
                break;
                }
            }
        }
    }

    void from_json(const Json &j, wxj::Config &c)
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
            Json j = Json::parse(file);

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
