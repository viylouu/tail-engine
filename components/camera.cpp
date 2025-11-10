#include "camera.hpp"

#include <wraps/renderTarget.hpp>
#include <core/macros.h>
#include <stdlib.h>

namespace tail {
    Camera::Camera(s32 width, s32 height) {
        out = new RenderTarget(width, height);
        proj = (mat4*)NEW(mat4);
        mat4_ortho(proj, 0, out->targ->texture->width, 0, out->targ->texture->height, -1,1);
        name = "Camera";
    }

    Camera::~Camera() {
        free(proj);
        delete out;
    }
}
