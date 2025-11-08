#pragma once

#include <node/component.hpp>
#include <wraps/renderTarget.hpp>

namespace tail {
    class Camera : public Component {
public:
        //mat4 proj;
        RenderTarget* out;
        b8 is_master;

        Camera(s32 width, s32 height);
        ~Camera();
    };   
}

