#pragma once

#include <wraps/renderTarget.hpp>
#include <render/agnostic.h>
#include <cstdlib>
#include <cmath>
#include <core/matrix.h>
#include <wraps/texture.hpp>

namespace tail {
    extern FUR_renderState* render;

    void render_new();
    void render_delete();

    namespace draw {
        void flush();

        struct PAR_clear {
            v3 col               = v3{0};
            RenderTarget* target = NULL;
        };

        void clear(PAR_clear clr);

        struct PAR_rend_gen {
            RenderTarget* target = NULL;
            mat4* transf         = mat4_identity_ptr;
            mat4* proj           = NULL;
        };


        struct PAR_rect {
            PAR_rend_gen gen;
            v2 pos  = v2{0};
            v2 size = v2{0};
            v4 col  = v4{1};
        };

        void rect(PAR_rect rect);

        struct PAR_tex {
            PAR_rend_gen gen;
            Texture* texture = NULL;
            v2 pos           = v2{0};
            v2 size          = v2{NAN};
            v4 col           = v4{1};
            v4 sample        = v4{NAN};
        };

        void tex(PAR_tex tex);

        struct PAR_renderTarget {
            PAR_rend_gen gen;
            RenderTarget* target = NULL;
            v2 pos               = v2{0};
            v2 size              = v2{NAN};
            v4 col               = v4{1};
            v4 sample            = v4{NAN};
        };

        void renderTarget(PAR_renderTarget targ);
    }
}
