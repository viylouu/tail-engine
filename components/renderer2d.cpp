#include "renderer2d.hpp"

#include <nouser/state.hpp>
#include <render/draw.h>
#include <node/node.hpp>

#include <deps/imgui/imgui.h>

namespace tail {
    void Renderer2d::init() { 
        name = "Renderer2d"; 

        vars.push_back(Variable{
                &typedata,
                sizeof(typedata),
                VarType::CUSTOM,
                "type data",
                [&]() {
                    s32 type = typedata.index();
                    ImGui::Combo("type", &type, (const char*[]){ "Rect", "Texture" }, 2);
                    
                    if (type != (s32)typedata.index()) 
                        switch (type) {
                            case 0: typedata = Renderer2d::Rect{ .col = v4{1,1,1,1} }; break;
                            case 1: typedata = Renderer2d::Tex{ .tex = NULL, .tint = v4{1,1,1,1}, .sample = v4{0,0,16,16} }; break;
                        }

                    if (std::holds_alternative<Renderer2d::Rect>(typedata)) {
                        Renderer2d::Rect& r = std::get<Renderer2d::Rect>(typedata);
                        f32 c[4] = { r.col.r, r.col.g, r.col.b, r.col.a };
                        ImGui::ColorPicker4("Color", c);
                        r.col.r = c[0];
                        r.col.g = c[1];
                        r.col.b = c[2];
                        r.col.a = c[3];
                    } else if (std::holds_alternative<Renderer2d::Tex>(typedata)) {
                        //Renderer2d::Tex& t = std::get<Renderer2d::Tex>(typedata);
                        // todo: do
                    }
                }
            });
    }

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
