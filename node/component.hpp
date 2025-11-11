#pragma once

#include <core/macros.h>
#include <string>
#include <node/node.hpp>

namespace tail {
    class Node;

    class Component {
public:
        Node* node;

        std::string name;

        virtual ~Component()        { }
        virtual void init()         { }
        virtual void update(f32 dt) { UNUSED(dt); }
        virtual void exit()         { }
    };
}
