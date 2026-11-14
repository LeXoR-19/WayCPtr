#pragma once

#include <cstdint>
#include <array>

enum class Anchor : uint8_t {
    None   = 0,
    Top    = 1 << 0,  // 0001
    Bottom = 1 << 1,  // 0010
    Left   = 1 << 2,  // 0100
    Right  = 1 << 3,  // 1000
};

inline Anchor operator|(Anchor a, Anchor b) {
    return static_cast<Anchor>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inline bool has_anchor(Anchor set, Anchor check) {
    return (static_cast<uint8_t>(set) & static_cast<uint8_t>(check)) != 0;
}

enum class Position : uint8_t {
    Top,
    Bottom,
    Left,
    Right,
};

enum class Orientation : uint8_t {
    Horizontal,
    Vertical,
};

enum class Layer : uint8_t {
    Background,
    Bottom,
    Top,
    Overlay,
};

enum class PanelZone : uint8_t {
    Left,
    Center,
    Right,
};

struct config {
    int width { -1 };
    int height { 40 };

    // top, right, bottom, left
    std::array<int, 4> margin {0, 0, 0, 0};
    std::array<int, 4> padding {0, 0, 0, 0};

    Position position { Position::Top };
    Orientation orientation { Orientation::Horizontal };
    Layer layer { Layer::Top };

    Anchor anchors { Anchor::Top | Anchor::Left | Anchor::Right };
    bool exclusive_zone { true };
};
