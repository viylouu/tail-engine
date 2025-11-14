#include "tail.hpp"
#include <iostream>

#include <nouser/state.hpp>

#include <platf/agnostic.h>
#include <render/agnostic.h>
#include <render/draw.h>
#include <core/input.h>
#include <core/time.h>
#include <debug/debug.hpp>

extern tail::Program* create_game();

namespace tail {
    void clear_cams(Node* node) {
        for (Component* comp : node->components) {
            if ( Camera* cam = dynamic_cast<Camera*>(comp) )
                if (!IS_NAN(cam->bgcolor.x) && !IS_NAN(cam->bgcolor.y) && !IS_NAN(cam->bgcolor.z))
                    IMPL_fur_render_clear(state::render, OP_fur_render_clear{
                            .target = cam->out->targ,
                            .col    = cam->bgcolor
                        });
        }

        for (Node* child : node->children)
            clear_cams(child);
    }

    void run(Program* program, FUR_platfState* platf, FUR_renderState* render) {
        ERROR_IF(!program, "tf you think will happen?\n");

        Settings sets = {};
        sets.bgcolor = v3{0,0,0};

        program->scene = new Node();
        program->scene->name = "scene";

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

            debug_startFrame();

            if (!IS_NAN(sets.bgcolor.x) && !IS_NAN(sets.bgcolor.y) && !IS_NAN(sets.bgcolor.z))
                IMPL_fur_render_clear(render, OP_fur_render_clear{
                        .target = NULL,
                        .col    = sets.bgcolor
                    });

            clear_cams(program->scene);

            program->preupdate(time->delta);
            program->scene->update(time->delta);
            program->postupdate(time->delta);
            
            Camera* cam = program->scene->find_master_cam();
            if (cam)
                IMPL_fur_render_renderTarget(render, OP_fur_render_renderTarget{
                            .out_target = NULL,
                            .in_target = cam->out->targ,
                            .pos = v2{0,0},
                            .size = v2{(f32)render->width,(f32)render->height},
                            .sample = v4{0,0,(f32)cam->out->targ->texture->width,(f32)cam->out->targ->texture->height},
                            .col = v4{1,1,1,1},
                            .transf = mat4_identity_ptr,
                            .proj = NULL
                        });

            fur_render_flush(render);

            debug_endFrame(program->scene);

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

    mat4_init();

    state::platf = IMPL_fur_platf_constr(OP_fur_platf_constr{
            .title = (char*)"window",
            .dims  = v2{800,600},
            .platf = FUR_PLATF_GLFW
        });

    state::render = IMPL_fur_render_constr(OP_fur_render_constr{
            .api = FUR_RENDER_API_GL
        });

    fur_platf_setRender(state::platf, state::render);

    debug_init();

    run(program, state::platf, state::render);

    debug_end();

    fur_render_destr(state::render);
    fur_platf_destr(state::platf);

    mat4_deinit();

    delete program;
    return 0;
}
