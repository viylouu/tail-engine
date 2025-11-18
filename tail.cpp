#include "tail.hpp"

#include <platf/agnostic.h>
//#include <render/agnostic.h>
//#include <render/draw.h>
#include <core/macros.h>
#include <core/time.h>
#include <core/input.h>
#include <wraps/render.hpp>

int main() {
    mat4_init();

    FUR_platfState* Splatf = IMPL_fur_platf_constr(OP_fur_platf_constr{
            .title = (char*)"untitled",
            .dims = v2{800,600},
            .platf = FUR_PLATF_GLFW
        });

    tail::render_new();

    fur_platf_setRender(Splatf, tail::render);

    FUR_timer* time = IMPL_fur_makeTimer(OP_fur_makeTimer{ .plat = FUR_PLATF_GLFW, .off = 0 });

    init();

    while (!fur_platf_shouldWindowClose(Splatf)) {
        fur_platf_poll(Splatf);
        fur_input_poll(Splatf);
        fur_updateTimers(&time, 1);

        //fur_render_clear(render);
        //fur_render_rect(render);
        
        update();
        render();

        tail::draw::flush();
        fur_platf_present(Splatf);
    }
    
    exit();

    fur_destroyTimer(time);

    tail::render_delete();
    fur_platf_destr(Splatf);

    mat4_deinit();
}
