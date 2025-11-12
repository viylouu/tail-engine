#include "camera.hpp"

#include <wraps/renderTarget.hpp>
#include <core/macros.h>
#include <stdlib.h>
#include <nouser/state.hpp>

namespace tail {
    Camera::Camera(s32 width, s32 height) {
        out = new RenderTarget(width, height);
        proj = (mat4*)NEW(mat4);
        transf = (mat4*)NEW(mat4);
        transf_proj = (mat4*)NEW(mat4);
        mat4_ortho(proj, 0, out->targ->texture->width, 0, out->targ->texture->height, -1,1);
        name = "Camera";
    }

    Camera::~Camera() {
        free(transf_proj);
        free(transf);
        free(proj);
        delete out;
    }

    void Camera::update(f32 dt) {
        UNUSED(dt);

        mat4_translate(transf, -node->pos.x, -node->pos.y, -node->pos.z);

        mat4 a;
        mat4_rotateX(&a, node->rot.x);
        mat4_multiply(transf, *transf, a);

        mat4_rotateY(&a, node->rot.y);
        mat4_multiply(transf, *transf, a);

        mat4_rotateZ(&a, node->rot.z);
        mat4_multiply(transf, *transf, a);

        mat4_scale(&a, node->scale.x, node->scale.y, node->scale.z);
        mat4_multiply(transf, *transf, a);

        mat4_translate(&a, out->targ->texture->width/2.f, out->targ->texture->height/2.f, 0);
        mat4_multiply(transf, *transf, a);

        mat4_multiply(transf_proj, *transf, *proj);
    }

    Camera* Camera::add_to(Node* parent) {
        return (Camera*)parent->add_component((Component*)this);
    }

    v3 Camera::mouse_to_this(v2 mouse) {
        v2 scaled = mouse / v2{(f32)state::render->width, (f32)state::render->height} * v2{(f32)out->targ->texture->width, (f32)out->targ->texture->height};
        scaled -= v2{(f32)out->targ->texture->width, (f32)out->targ->texture->height} / 2.f;
        v4 transfd;
        mat4_multiply_vector(&transfd, *transf, v4{scaled.x,scaled.y,0,1});
        return v3{transfd.x,transfd.y,transfd.z};
    }
}
