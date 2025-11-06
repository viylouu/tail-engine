#pragma once

#include <core/macros.h>

namespace tail {
    struct Settings {
        v3 bgcolor;
    };

    class Program {
public:
        virtual ~Program()               { }
        virtual void init(Settings* set) { UNUSED(set);  }
        virtual void update(f32 dt)      { UNUSED(dt); }
        virtual void exit()              { }
    };

    void run(Program* program);
}
