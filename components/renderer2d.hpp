#pragma once

#include <node/node.hpp>

#include <variant>

namespace tail {
    class Renderer2d : public Component {
public:
        struct Rect {
            v4 col;
        };

        std::variant<Rect> typedata;

        void update(f32 dt);
    };
}
