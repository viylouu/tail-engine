#include <tail.hpp>
#include <iostream>

class Game : public tail::Program {
public:
    void init() override {}
    void exit() override {}

    void update(f32 dt) override { 
        std::cout << 1.f/dt << " FPS\n";
    }
};

tail::Program* create_game() {
    return new Game();
}
