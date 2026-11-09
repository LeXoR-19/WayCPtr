#pragma once

#include <cstdint>
#include <array>

namespace pan {

enum class position : int8_t {
    top,
    bottom,
    left,
    right,
};

enum class orientation : int8_t {
    horizontal,
    vertical,
};

// -1 = auto

struct config {
    int width { -1 };
    int height { 40 };

    //[top, right, bottom, left]
    std::array<int, 4> margin{};
    std::array<int, 4> padding{};

    position pos { position::top };
    orientation orient { orientation::horizontal };


};

}
