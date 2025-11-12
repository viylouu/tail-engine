#pragma once

#include <node/component.hpp>
#include <wraps/renderTarget.hpp>
#include <core/matrix.h>

namespace tail {
    class Camera : public Component {
public:
        mat4* transf;
        mat4* proj;
        RenderTarget* out;
        b8 is_master;

        Camera(s32 width, s32 height);
        ~Camera();

        void update(f32 dt);

        Camera* add_to(Node* parent);
    };   
}

