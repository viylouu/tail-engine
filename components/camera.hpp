#pragma once

#include <node/component.hpp>
#include <wraps/renderTarget.hpp>
#include <core/matrix.h>

namespace tail {
    class Camera : public Component {
public:
        mat4* transf;
        mat4* proj;
        mat4* transf_proj;
        RenderTarget* out;
        b8 is_master;
        v3 bgcolor;

        Camera(s32 width, s32 height);
        ~Camera();

        void update(f32 dt);

        Camera* add_to(Node* parent);

        v3 screen_to_this(v2 mouse);
        v3 mouse_to_this();
    };   
}

