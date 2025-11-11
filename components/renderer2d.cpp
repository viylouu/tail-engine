#include "renderer2d.hpp"

#include <nouser/state.hpp>
#include <render/draw.h>
#include <node/node.hpp>

namespace tail {
    void Renderer2d::init() { name = "Renderer2d"; }

    void Renderer2d::update(f32 dt) {
        UNUSED(dt);

        v2 pos{node->pos.x,   node->pos.y};
        v2 size{node->scale.x, node->scale.y};
        pos -= size / 2.f;

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
                        .pos    = pos,
                        .size   = size,
                        .col    = std::get<Renderer2d::Rect>(typedata).col,
                        .transf = mat4_identity_ptr,
                        .proj   = camproj
                    });
            } else if (std::holds_alternative<Renderer2d::Tex>(typedata)) {
                IMPL_fur_render_tex(state::render, OP_fur_render_tex{
                        .target  = camout,
                        .texture = std::get<Renderer2d::Tex>(typedata).tex->tex,
                        .pos     = pos,
                        .size    = size,
                        .sample  = std::get<Renderer2d::Tex>(typedata).sample,
                        .col     = std::get<Renderer2d::Tex>(typedata).tint,
                        .transf  = mat4_identity_ptr,
                        .proj    = camproj
                    });
            }
        }
    }
}
