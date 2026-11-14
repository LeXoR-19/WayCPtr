#pragma once

#include <panel-conf.hpp>
#include <functional>
#include <sol/sol.hpp>

namespace lua::api {

using PanelCallback = std::function<void(const config&)>;

inline void panel_config(sol::table& waycptr, PanelCallback callback) {
    waycptr.set_function("config", [callback](sol::table t) {
        config conf;
        
        // Высота
        if (t["height"].valid())
            conf.height = t["height"];
        // Ширина
        if (t["width"].valid())
            conf.width = t["width"];
        // Ориентация
        if (t["orientation"].valid()) {
            std::string o { t["orientation"] };
            conf.orientation = (o == "vertical") ? Orientation::Vertical : Orientation::Horizontal;
        }
        // Слой
        if (t["layer"].valid()) {
            std::string l { t["layer"] };

            if (l == "background")
                conf.layer = Layer::Background;
            else if (l == "bottom")
                conf.layer = Layer::Bottom;
            else if (l == "top")
                conf.layer = Layer::Top;
            else if (l == "overlay")
                conf.layer = Layer::Overlay;
        }
        // Якоря
        if (t["anchors"].valid()) {
            std::string a { t["anchors"] };
            conf.anchors = Anchor::None;

            if (a.find("top") != std::string::npos)
                conf.anchors = conf.anchors | Anchor::Top;
            if (a.find("bottom") != std::string::npos)
                conf.anchors = conf.anchors | Anchor::Bottom;
            if (a.find("left") != std::string::npos)
                conf.anchors = conf.anchors | Anchor::Left;
            if (a.find("right") != std::string::npos)
                conf.anchors = conf.anchors | Anchor::Right;
        }
        // Эксклюзивная зона
        if (t["exclusive_zone"].valid())
            conf.exclusive_zone = t["exclusive_zone"];
        // Внешние отступы
        if (t["margin"].valid()) {
            sol::table m { t["margin"] };
            conf.margin[0] = m[1].get_or(0);
            conf.margin[1] = m[2].get_or(0);
            conf.margin[2] = m[3].get_or(0);
            conf.margin[3] = m[4].get_or(0);
        }
        // Внутренние отступы
        if (t["padding"].valid()) {
            sol::table p { t["padding"] };
            conf.padding[0] = p[1].get_or(0);
            conf.padding[1] = p[2].get_or(0);
            conf.padding[2] = p[3].get_or(0);
            conf.padding[3] = p[4].get_or(0);
        }

        // Вызов колбека
        if (callback)
            callback(conf);
    });
}

}
