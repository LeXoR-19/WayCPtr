#pragma once

#include <panel-conf.hpp>
#include <widget-conf.hpp>

#include <functional>
#include <string>

namespace callback {

/*
 * params:
 *  1) type:            const std::string
 *  2) object_name:     const std::string
 *  3) zone:            const std::string
 *  4) width:           int
 *  5) heigth:          int
*/
using AddWidget = std::function<void(
    const std::string&,
    const std::string&,
    const std::string&,
    int, int
)>;

/*
 * params:
 *  - config:    pan(el)::config
*/
using SetPanelConfig = std::function<void(const pan::config&)>;

}
