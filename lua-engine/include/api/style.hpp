#pragma once

#include <functional>
#include <sol/sol.hpp>

namespace lua::api {

using StyleCallback = std::function<void(const std::string& path)>;

inline void style(sol::table& waycptr, StyleCallback callback) {
    waycptr.set_function("style", [callback](const std::string& path) {
        if (callback)
            callback(path);
    });
}




}
