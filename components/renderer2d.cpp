#include "renderer2d.hpp"

#include <nouser/state.hpp>
#include <render/draw.h>

namespace tail {
    void Renderer2d::update(f32 dt) {
        UNUSED(dt);

        if (std::holds_alternative<Renderer2d::Rect>(typedata)) {
            IMPL_fur_render_rect(state::render, OP_fur_render_rect{
                    .target = NULL,
                    .pos    = v2{node->pos.x,node->pos.y},
                    .size   = v2{node->scale.x,node->scale.y},
                    .col    = std::get<Renderer2d::Rect>(typedata).col,
                    .transf = mat4_identity
                });
        }
    }
}
