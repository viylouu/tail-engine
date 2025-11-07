#include "tail.hpp"
#include <iostream>

#include <nouser/state.hpp>

#include <platf/agnostic.h>
#include <render/agnostic.h>
#include <render/draw.h>
#include <core/input.h>
#include <core/time.h>

extern tail::Program* create_game();

namespace tail {
    void run(Program* program, FUR_platfState* platf, FUR_renderState* render) {
        ERROR_IF(!program, "tf you think will happen?\n");

        Settings sets = {};
        sets.bgcolor = v3{0,0,0};

        program->scene = new Node();

        program->init(&sets);
        program->scene->init();

        FUR_timer* time = IMPL_fur_makeTimer(OP_fur_makeTimer{
                .plat = FUR_PLATF_GLFW,
                .off  = 0
            });

        while (!fur_platf_shouldWindowClose(platf)) {
            fur_platf_poll(platf);
            fur_input_poll(platf);
            fur_updateTimers(&time, 1);

            if (!IS_NAN(sets.bgcolor.x) && !IS_NAN(sets.bgcolor.y) && !IS_NAN(sets.bgcolor.z))
                IMPL_fur_render_clear(render, OP_fur_render_clear{
                        .target = NULL,
                        .col    = sets.bgcolor
                    });

            program->preupdate(time->delta);
            program->scene->update(time->delta);
            program->postupdate(time->delta);

            fur_render_flush(render);
            fur_platf_present(platf);
        }

        fur_destroyTimer(time);

        program->scene->exit();
        program->exit();

        delete program->scene;
    }
}

int main(void) {
using namespace tail;
    Program* program = create_game();
    ERROR_IF(!program, "failed to create game!\n");

    state::platf = IMPL_fur_platf_constr(OP_fur_platf_constr{
            .title = (char*)"window",
            .dims  = v2{800,600},
            .platf = FUR_PLATF_GLFW
        });

    state::render = IMPL_fur_render_constr(OP_fur_render_constr{
            .api = FUR_RENDER_API_GL
        });

    fur_platf_setRender(state::platf, state::render);

    run(program, state::platf, state::render);

    fur_render_destr(state::render);
    fur_platf_destr(state::platf);

    delete program;
    return 0;
}
