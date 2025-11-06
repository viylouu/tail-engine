#include "tail.hpp"
#include <iostream>

#include <platf/agnostic.h>
#include <render/agnostic.h>
#include <render/draw.h>
#include <core/input.h>
#include <core/time.h>

extern tail::Program* create_game();

namespace tail {
    void run(Program* program, FUR_platfState* platf, FUR_renderState* render) {
        Settings sets = {};
        sets.bgcolor = v3{0,0,0};

        if (program) program->init(&sets);

        FUR_timer* time = IMPL_fur_makeTimer(OP_fur_makeTimer{
                FUR_PLATF_GLFW,
                0
            });

        while (!fur_platf_shouldWindowClose(platf)) {
            fur_platf_poll(platf);
            fur_input_poll(platf);
            fur_updateTimers(&time, 1);

            IMPL_fur_render_clear(render, OP_fur_render_clear{
                    NULL, 
                    sets.bgcolor
                });

            program->update(time->delta);

            fur_render_flush(render);
            fur_platf_present(platf);
        }

        fur_destroyTimer(time);

        if (program) program->exit();
    }
}

int main(void) {
    tail::Program* program = create_game();
    ERROR_IF(!program, "failed to create game!\n");

    FUR_platfState* platf = IMPL_fur_platf_constr(OP_fur_platf_constr{
            (char*)"window",
            v2{800,600},
            FUR_PLATF_GLFW
        });

    FUR_renderState* render = IMPL_fur_render_constr(OP_fur_render_constr{
            FUR_RENDER_API_GL
        });

    fur_platf_setRender(platf, render);

    tail::run(program, platf, render);

    fur_render_destr(render);
    fur_platf_destr(platf);

    delete program;
    return 0;
}
