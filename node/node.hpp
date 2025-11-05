#pragma once

#include <vector>

#include <core/macros.h>

namespace tail {
    class Component {
public:
        virtual ~Component()        { }
        virtual void init()         { }
        virtual void update(f32 dt) { UNUSED(dt); }
        virtual void exit()         { }
    };

    class Node {
        std::vector<Component*> components;
        std::vector<Node*> children;

        ~Node();

        void init();
        void update(f32 dt);
        void exit();
    };
}
