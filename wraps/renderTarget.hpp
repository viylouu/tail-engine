#pragma once

#include <core/renderTarget.h>

namespace tail {
    class RenderTarget {
public:
        FUR_renderTarget* ul;
public:
        RenderTarget(s32 width, s32 height);
        ~RenderTarget();

        void resize(s32 width, s32 height);
    };
}
