#pragma once

#include <vector>

#include <core/macros.h>
#include <core/matrix.h>

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

    class Node {
public:
        v3 pos, rot, scale;
        mat4 transf;

        std::vector<Component*> components;
        std::vector<Node*> children;

        ~Node();

        void init();
        void update(f32 dt);
        void exit();

        Node* add_child(Node* child);
        Component* add_component(Component* comp);
    };
}
