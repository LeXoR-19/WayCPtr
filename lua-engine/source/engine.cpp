#include <engine.hpp>

#include <QFileInfo>

namespace lua {

void engine::init() {
    this->lua_.open_libraries(
        sol::lib::base,
        sol::lib::os
    );
    this->registerAPI();
}

void engine::registerAPI() noexcept {
    auto waycptr { this->lua_.create_named_table("waycptr") };
    // API registered
    api::panel_config(waycptr, this->panel_callback_);
    api::style(waycptr, this->style_callback_);
} 

void engine::set_panel_callback(api::PanelCallback callback) {
    this->panel_callback_ = std::move(callback);
}

void engine::set_style_callback(api::StyleCallback callback) {
    this->style_callback_ = std::move(callback);
}

bool engine::load_config(const QString& _path) {
    QFileInfo fi(_path);

    if (!fi.exists()) {
        qCritical() << "Файл не найден: " << _path;
        return false;
    }

    try {
        this->lua_.script_file(_path.toStdString());
        qDebug() << "Lua-конфиг загружен!";
        return true;
    } catch (const sol::error& e) {
        qCritical() << "Lua error: " << e.what();
        return false;
    }
}



}
