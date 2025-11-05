#pragma once

#include <core/macros.h>

namespace tail {
    class Program {
public:
        virtual ~Program()          { }
        virtual void init()         { }
        virtual void update(f32 dt) { UNUSED(dt); }
        virtual void exit()         { }
    };

    void run(Program* program);
}
