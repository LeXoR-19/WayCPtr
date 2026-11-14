#pragma once

#include <api/panel-api.hpp>
#include <api/style.hpp>
#include <QString>
#include <sol/sol.hpp>

namespace lua {

class engine {
private:
    sol::state lua_;
    api::PanelCallback panel_callback_;
    api::StyleCallback style_callback_;
public:
    engine() = default;;
    ~engine() = default;
    
    void init();

    void set_panel_callback(api::PanelCallback callback);
    void set_style_callback(api::StyleCallback callback);

    [[nodiscard]] bool load_config(const QString& _path);
private:
    void registerAPI() noexcept;
};

}
