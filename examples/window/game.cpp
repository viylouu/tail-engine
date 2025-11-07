#include <tail.hpp>

class Game : public tail::Program {
public:
    void init(tail::Settings* sets) {
        sets->bgcolor = v3{.2, .4, .3};

        tail::Node* n = scene->add_child(nullptr);

        tail::Renderer2d* r2d = (tail::Renderer2d*)n->add_component(new tail::Renderer2d());
        r2d->type = tail::Renderer2d::Type::Rect;
        r2d->tint = v4{1,0,0,1};

        n->pos = v3{0,0,0};
        n->scale = v3{64,64,1};
        n->rot = v3{0,0,0};
    }
};

tail::Program* create_game() {
    return new Game();
}
