#include "node.hpp"

#include <core/macros.h>
#include <components/camera.hpp>

namespace tail {
    Node::Node() { name = "Node"; scale = v3{1,1,1}; transf = (mat4*)NEW(mat4); }

    Node::~Node() {
        for (Component* comp : components)
            delete comp;
        for (Node* child : children)
            delete child;

        free(transf);
    }

    void Node::init() {
        for (Component* comp : components)
            comp->init();
        for (Node* child : children)
            child->init();
    }

    void Node::update(f32 dt) {
        mat4_translate(transf, pos.x, pos.y, pos.z);

        mat4 a;
        mat4_rotateX(&a, rot.x);
        mat4_multiply(transf, a, *transf);

        mat4_rotateY(&a, rot.y);
        mat4_multiply(transf, a, *transf);

        mat4_rotateZ(&a, rot.z);
        mat4_multiply(transf, a, *transf);

        mat4_scale(&a, scale.x, scale.y, scale.z);
        mat4_multiply(transf, a, *transf);

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

    Node* Node::add_to(Node* parent) {
        return parent->add_child(this);
    }
}
