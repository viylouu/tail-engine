#include "renderTarget.hpp"

#include <cstdlib>
#include <nouser/state.hpp>

namespace tail {
    RenderTarget::RenderTarget(s32 width, s32 height) {
        FUR_renderTarget* targ = IMPL_fur_renderTarget_constr(width, height, OP_fur_renderTarget_constr{ .api = FUR_RENDER_API_GL });
        spec = targ->spec;
        *CAST(FUR_renderTarget*, spec) = *this; // hacky
        api = targ->api;
        texture = targ->texture;
        free(targ);
    }

    RenderTarget::~RenderTarget() {
        fur_renderTarget_destr(this);
    }

    void RenderTarget::resize(s32 width, s32 height) {
        fur_renderTarget_resize(this, width, height);
    }
}
