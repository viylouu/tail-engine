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
}
