#pragma once

#include <platf/agnostic.h>
#include <render/agnostic.h>

namespace tail {
    namespace state {
        extern FUR_platfState* platf;
        extern FUR_renderState* render;

        extern bool is_debug;
    }
}
