#pragma once

#include <node/node.hpp>
#include <wraps/renderTarget.hpp>

namespace tail {
    class Camera : public Component {
public:
        //mat4 proj;
        RenderTarget* out;

        Camera(s32 width, s32 height);
        ~Camera();
    };   
}

