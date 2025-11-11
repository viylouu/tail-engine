#include "renderer2d.hpp"

#include <nouser/state.hpp>
#include <render/draw.h>
#include <node/node.hpp>

namespace tail {
    void Renderer2d::init() { name = "Renderer2d"; }

    void Renderer2d::update(f32 dt) {
        UNUSED(dt);

        for (Camera* cam : cams) {
            FUR_renderTarget* camout = state::render->defTarget;
            mat4* camproj = NULL;

            if (cam) {
                camout = cam->out->targ;
                camproj = cam->transf;
            }

            if (std::holds_alternative<Renderer2d::Rect>(typedata)) {
                IMPL_fur_render_rect(state::render, OP_fur_render_rect{
                        .target = camout,
                        .pos    = v2{node->pos.x,   node->pos.y},
                        .size   = v2{node->scale.x, node->scale.y},
                        .col    = std::get<Renderer2d::Rect>(typedata).col,
                        .transf = mat4_identity_ptr,
                        .proj   = camproj
                    });
            } else if (std::holds_alternative<Renderer2d::Tex>(typedata)) {
                IMPL_fur_render_tex(state::render, OP_fur_render_tex{
                        .target  = camout,
                        .texture = std::get<Renderer2d::Tex>(typedata).tex->tex,
                        .pos     = v2{node->pos.x,   node->pos.y},
                        .size    = v2{node->scale.x, node->scale.y},
                        .sample  = std::get<Renderer2d::Tex>(typedata).sample,
                        .col     = std::get<Renderer2d::Tex>(typedata).tint,
                        .transf  = mat4_identity_ptr,
                        .proj    = camproj
                    });
            }
        }
    }
}
