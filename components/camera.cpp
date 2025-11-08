#include "camera.hpp"

#include <wraps/renderTarget.hpp>

namespace tail {
    Camera::Camera(s32 width, s32 height) {
        out = new RenderTarget(width, height);
        //mat4_ortho(proj, );
        name = "Camera";
    }

    Camera::~Camera() {
        delete out;
    }
}
