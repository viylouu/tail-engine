#pragma once

#include <core/macros.h>
#include <node/node.hpp>

#include <components/renderer2d.hpp>

namespace tail {
    struct Settings {
        v3 bgcolor;
    };

    class Program {
public:
        Node* scene;

        virtual ~Program()               { }
        virtual void init(Settings* set) { UNUSED(set);  }
        virtual void preupdate(f32 dt)   { UNUSED(dt); }
        virtual void postupdate(f32 dt)  { UNUSED(dt); }
        virtual void exit()              { }
    };

    void run(Program* program);
}
