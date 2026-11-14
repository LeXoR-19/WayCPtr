#pragma once

#include <string>
#include <unordered_map>
#include <variant>
#include <concepts>


namespace widget {

using ExtraValue = std::variant<std::string, int, bool>;

template<typename T>
concept ExtraType = std::same_as<T, std::string> || std::same_as<T, int> || std::same_as<T, bool>;

struct config {
    std::string type;
    std::string name;
    std::string zone;
    int width { 100 };
    int height { 30 };

    std::unordered_map<std::string, ExtraValue> extra;
};

template<ExtraType T>
inline T get(const config& conf, const std::string& key, T def) {
    auto it { conf.extra.find(key) };
    if (it != conf.extra.end() && std::holds_alternative<T>(it->second))
        return std::get<T>(it->second);
    return def;
}

}
