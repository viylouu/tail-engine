#include "renderer2d.hpp"

#include <nouser/state.hpp>
#include <render/draw.h>

namespace tail {
    void Renderer2d::update(f32 dt) {
        UNUSED(dt);

        switch (type) {
            case Type::Rect:
                IMPL_fur_render_rect(state::render, OP_fur_render_rect{
                        nullptr,
                        v2{node->pos.x,node->pos.y},
                        v2{node->scale.x,node->scale.y},
                        tint,
                        mat4_identity
                    });
                break;
        }
    }
}
