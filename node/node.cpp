#include "node.hpp"

#include <core/macros.h>
#include <components/camera.hpp>

namespace tail {
    Node::Node() { name = "Node"; }

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

    Node* Node::add_child(Node* child) {
        if (!child) child = new Node();
        children.push_back(child);
        return child;
    }

    Camera* Node::find_master_cam() {
        for (Component* comp : components) {
            if ( Camera* cam = dynamic_cast<Camera*>(comp) )
                if (cam->is_master)
                    return cam;
        }

        for (Node* child : children) {
            Camera* cam = child->find_master_cam();
            if (cam)
                return cam;
        }

        return NULL;
    }
    
    Component* Node::add_component(Component* comp) {
        components.push_back(comp);
        comp->node = this;
        return comp;
    }
}
