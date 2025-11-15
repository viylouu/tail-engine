#pragma once

#include <core/macros.h>
#include <string>
#include <node/node.hpp>
#include <node/variable.hpp>

namespace tail {
    class Node;

    class Component {
public:
        Node* node;

        bool DEBUG_expanded;

        std::string name;

        std::vector<Variable> vars;

        Component() { DEBUG_expanded = false; }

        virtual ~Component()        { }
        virtual void init()         { }
        virtual void update(f32 dt) { UNUSED(dt); }
        virtual void exit()         { }
    };
}
