#pragma once

#include <node/node.hpp>
#include <wraps/texture.hpp>

#include <variant>

namespace tail {
    class Renderer2d : public Component {
public:
        struct Rect {
            v4 col;
        };

        struct Tex {
            tail::Texture* tex;
            v4 tint;
            v4 sample;
        };

        std::variant<Rect, Tex> typedata;

        void update(f32 dt);
    };
}
