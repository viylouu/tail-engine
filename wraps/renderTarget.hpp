#pragma once

#include <core/renderTarget.h>

namespace tail {
    struct RenderTarget : FUR_renderTarget {
        RenderTarget(s32 width, s32 height);
        ~RenderTarget();

        void resize(s32 width, s32 height);
    };
}
