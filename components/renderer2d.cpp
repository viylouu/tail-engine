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
                camproj = cam->transf_proj;
            }

            if (std::holds_alternative<Renderer2d::Rect>(typedata)) {
                IMPL_fur_render_rect(state::render, OP_fur_render_rect{
                        .target = camout,
                        .pos    = -v2{.5f},
                        .size   = v2{1},
                        .col    = std::get<Renderer2d::Rect>(typedata).col,
                        .transf = node->transf,
                        .proj   = camproj
                    });
            } else if (std::holds_alternative<Renderer2d::Tex>(typedata)) {
                IMPL_fur_render_tex(state::render, OP_fur_render_tex{
                        .target  = camout,
                        .texture = std::get<Renderer2d::Tex>(typedata).tex->tex,
                        .pos     = -v2{.5f},
                        .size    = v2{1},
                        .sample  = std::get<Renderer2d::Tex>(typedata).sample,
                        .col     = std::get<Renderer2d::Tex>(typedata).tint,
                        .transf  = node->transf,
                        .proj    = camproj
                    });
            }
        }
    }

    Renderer2d* Renderer2d::add_to(Node* parent) {
        return (Renderer2d*)parent->add_component((Component*)this);
    }
}
