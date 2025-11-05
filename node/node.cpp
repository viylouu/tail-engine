#include "node.hpp"

#include <core/macros.h>

namespace tail {
    Node::~Node() {
        for (Component* comp : components)
            delete comp;
        for (Node* child : children)
            delete child;
    }

    void Node::init() {
        for (Component* comp : components)
            comp->init();
        for (Node* child : children)
            child->init();
    }

    void Node::update(f32 dt) {
        for (Component* comp : components)
            comp->update(dt);
        for (Node* child : children)
            child->update(dt);
    }

    void Node::exit() {
        for (Component* comp : components)
            comp->exit();
        for (Node* child : children)
            child->exit();
    }
}
