#pragma once

#include <core/macros.h>

namespace tail {
    class Node;

    class Component {
public:
        Node* node;

        virtual ~Component()        { }
        virtual void init()         { }
        virtual void update(f32 dt) { UNUSED(dt); }
        virtual void exit()         { }
    };
}
