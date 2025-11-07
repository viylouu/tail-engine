#include <tail.hpp>

class Game : public tail::Program {
public:
    void init(tail::Settings* sets) {
        sets->bgcolor = v3{.2, .4, .3};

        tail::Node* n = scene->add_child(nullptr);
        UNUSED(n);
        n->add_component(new tail::comp::Renderer2d());
    }
};

tail::Program* create_game() {
    return new Game();
}
