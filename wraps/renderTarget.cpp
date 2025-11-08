#include "renderTarget.hpp"

#include <cstdlib>
#include <nouser/state.hpp>

namespace tail {
    RenderTarget::RenderTarget(s32 width, s32 height) {
        targ = IMPL_fur_renderTarget_constr(width, height, OP_fur_renderTarget_constr{ .api = FUR_RENDER_API_GL });
    }

    RenderTarget::~RenderTarget() {
        fur_renderTarget_destr(targ);
    }

    void RenderTarget::resize(s32 width, s32 height) {
        fur_renderTarget_resize(targ, width, height);
    }
}
