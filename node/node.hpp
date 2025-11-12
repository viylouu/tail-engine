#pragma once

#include <vector>
#include <string>
#include <node/component.hpp>
#include <core/macros.h>
#include <core/matrix.h>

namespace tail {
    class Camera;
    class Component;

    class Node {
public:
        v3 pos, rot, scale;
        mat4 transf;

        std::vector<Component*> components;
        std::vector<Node*> children;

        std::string name;

        Node();
        ~Node();

        void init();
        void update(f32 dt);
        void exit();

        Camera* find_master_cam();

        Node* add_child(Node* child);
        Component* add_component(Component* comp);
        Node* add_to(Node* parent);
    };
}
