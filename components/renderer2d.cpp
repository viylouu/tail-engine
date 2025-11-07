#include "renderer2d.hpp"

#include <nouser/state.hpp>
#include <render/draw.h>

namespace tail {
    void Renderer2d::update(f32 dt) {
        UNUSED(dt);

        if (std::holds_alternative<Renderer2d::Rect>(typedata)) {
            IMPL_fur_render_rect(state::render, OP_fur_render_rect{
                    NULL,                                       // target
                    v2{node->pos.x,node->pos.y},                // pos
                    v2{node->scale.x,node->scale.y},            // size
                    std::get<Renderer2d::Rect>(typedata).col,   // col
                    mat4_identity                               // transf
                });
        }
    }
}
