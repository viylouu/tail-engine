#include "render.hpp"

#include <render/draw.h>

namespace tail {
    FUR_renderState* render;

    void render_new() {
        render = IMPL_fur_render_constr({ FUR_RENDER_API_GL });
    }

    void render_delete() {
        fur_render_destr(render);
    }

    namespace draw {
        void flush() {
            fur_render_flush(render);
        }

        void clear(PAR_clear clr) {
            auto TARGUL = clr.target? clr.target->ul : NULL;
            IMPL_fur_render_clear(render, { TARGUL, clr.col });
        }

        void rect(PAR_rect rect) {
            auto TARGUL = rect.gen.target? rect.gen.target->ul : NULL;
            IMPL_fur_render_rect(render, { TARGUL, rect.pos, rect.size, rect.col, rect.gen.transf, rect.gen.proj });
        }

        void tex(PAR_tex tex) {
            auto TARGUL = tex.gen.target? tex.gen.target->ul : NULL;
            auto TEXUL = tex.texture? tex.texture->ul : NULL;
            IMPL_fur_render_tex(render, { TARGUL, TEXUL, tex.pos, tex.size, tex.sample, tex.col, tex.gen.transf, tex.gen.proj });
        }

        void renderTarget(PAR_renderTarget targ) {
            auto GTARGUL = targ.gen.target? targ.gen.target->ul : NULL;
            auto TARGUL = targ.target? targ.target->ul : NULL;
            IMPL_fur_render_renderTarget(render, { GTARGUL, TARGUL, targ.pos, targ.size, targ.sample, targ.col, targ.gen.transf, targ.gen.proj });
        }
    }
}
