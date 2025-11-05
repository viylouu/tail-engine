#pragma once

#include <core/macros.h>

namespace tail {
    class Program {
public:
        virtual ~Program() {}
        virtual void init() = 0;
        virtual void update(f32 dt) = 0;
        virtual void exit() = 0;
    };

    void run(Program* program);
}
