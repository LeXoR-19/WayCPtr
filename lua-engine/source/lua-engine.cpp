#include <lua-engine.hpp>

#include <sol/types.hpp>

#include <QFileInfo>
#include <qlogging.h>

namespace lua {

engine::engine() {
    this->lua_.open_libraries(
        sol::lib::base,
        sol::lib::string,
        sol::lib::os,
        sol::lib::math
    );

    this->registerAPI();
}

void engine::registerAPI() {
    auto waycptr { this->lua_.create_named_table("waycptr") };
}

bool engine::load_config(const QString& _path) {
    QFileInfo fi(_path);

    if (!fi.exists()) {
        qCritical() << "Файл не найден: " << _path;
        return false;
    }

    try {
        this->lua_.script_file(_path.toStdString());
        qDebug() << "Конфигурационный файл применен!";
        return true;
    } catch (const sol::error& e) {
        qCritical() << "Ошибка в Lua: " << e.what();
        return false;
    }
}

}
