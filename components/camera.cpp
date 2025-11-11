#include "camera.hpp"

#include <wraps/renderTarget.hpp>
#include <core/macros.h>
#include <stdlib.h>

namespace tail {
    Camera::Camera(s32 width, s32 height) {
        out = new RenderTarget(width, height);
        proj = (mat4*)NEW(mat4);
        transf = (mat4*)NEW(mat4);
        mat4_ortho(proj, 0, out->targ->texture->width, 0, out->targ->texture->height, -1,1);
        name = "Camera";
    }

    Camera::~Camera() {
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

        mat4_multiply(transf, *transf, *proj);
    }
}
