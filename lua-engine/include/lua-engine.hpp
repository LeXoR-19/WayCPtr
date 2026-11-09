#pragma once

#include <sol/state.hpp>

#include <QString>

namespace lua {

class engine {
private:
    sol::state lua_;
public:
    explicit engine();
    ~engine() = default;
    
    bool load_config(const QString& _path);
private:
    void registerAPI();
};

}
