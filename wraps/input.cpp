#include "input.hpp"

#include <core/input.h>

namespace tail {
    bool get_key(Key key) {
        return fur_input_isKeyHeld((FUR_key)key);
    }

    bool get_key_down(Key key) {
        return fur_input_isKeyPressed((FUR_key)key);
    }

    bool get_key_up(Key key) {
        return fur_input_isKeyReleased((FUR_key)key);
    }

    bool get_mouse(Mouse but) {
        return fur_input_isMouseHeld((FUR_mouse)but);
    }

    bool get_mouse_down(Mouse but) {
        return fur_input_isMousePressed((FUR_mouse)but);
    }
    
    bool get_mouse_up(Mouse but) {
        return fur_input_isMouseReleased((FUR_mouse)but);
    }

    v2 get_mouse_pos() {
        return fur_input_mouse_pos;
    }
}
