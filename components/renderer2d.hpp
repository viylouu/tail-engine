#pragma once

#include <node/node.hpp>

namespace tail {
    class Renderer2d : public Component {
public:
        enum class Type {
            Rect
        } type;

        v4 tint;

        void update(f32 dt);
    };
}
