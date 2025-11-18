#include "renderTarget.hpp"

namespace tail {
    RenderTarget::RenderTarget(s32 width, s32 height) {
        ul = IMPL_fur_renderTarget_constr(width, height, { FUR_RENDER_API_GL });
    }

    RenderTarget::~RenderTarget() {
        fur_renderTarget_destr(ul);
    }

    void RenderTarget::resize(s32 width, s32 height) {
        fur_renderTarget_resize(ul, width, height);
    }
}
