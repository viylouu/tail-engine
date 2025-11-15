#include <platf/agnostic.h>
#include <render/agnostic.h>
#include <render/draw.h>
#include <core/macros.h>
#include <core/time.h>
#include <core/input.h>

int main() {
    mat4_init();

    FUR_platfState* platf = IMPL_fur_platf_constr(OP_fur_platf_constr{
            .title = (char*)"untitled",
            .dims = v2{800,600},
            .platf = FUR_PLATF_GLFW
        });

    FUR_renderState* render = IMPL_fur_render_constr(OP_fur_render_constr{
            .api = FUR_RENDER_API_GL
        });

    fur_platf_setRender(platf, render);

    FUR_timer* time = IMPL_fur_makeTimer(OP_fur_makeTimer{ .plat = FUR_PLATF_GLFW, .off = 0 });

    while (!fur_platf_shouldWindowClose(platf)) {
        fur_platf_poll(platf);
        fur_input_poll(platf);
        fur_updateTimers(&time, 1);

        fur_render_clear(render);
        fur_render_rect(render);

        fur_render_flush(render);
        fur_platf_present(platf);
    }
    
    fur_destroyTimer(time);

    fur_render_destr(render);
    fur_platf_destr(platf);

    mat4_deinit();
}
