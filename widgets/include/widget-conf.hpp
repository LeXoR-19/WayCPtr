#pragma once

#include <string>

namespace widget {

struct config {
    std::string type;
    std::string object_name;
    std::string zone;
    int width { 100 };
    int height { 30 };
};

}
