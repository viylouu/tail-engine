#include <tail.hpp>

class Game : public tail::Program {
public:
    void update(f32 dt) { 
        UNUSED(dt);
    }
};

tail::Program* create_game() {
    return new Game();
}
