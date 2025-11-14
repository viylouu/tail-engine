#pragma once

#include <core/macros.h>
#include <node/node.hpp>

namespace tail {
    void debug_init();
    void debug_startFrame();
    void debug_endFrame(Node* scene);
    void debug_end();
}
