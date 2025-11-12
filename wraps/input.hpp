#pragma once

namespace tail {
    enum class Key {
// misc
    ESCAPE,
    CAPS,
    SPACE, TAB,
    BACKSPACE, DELETE,
    HOME, END,
    PAGEUP, PAGEDOWN,
    INSERT,

// modifiers
    LSHIFT, RSHIFT,
    LCTRL,  RCTRL,
    LALT,   RALT,
    LSUPER, RSUPER, // win key

// arrow keys
             UP,
    LEFT, RIGHT,
            DOWN, 

// alphabetical
    A, B, C,
    D, E, F, 
    G, H, I,
    J, K, L,
    M, N, O,
    P, Q, R,
    S, T, U,
    V, W, X,
          Y, Z,

// numerical
    ONE, TWO, THREE,
    FOUR, FIVE, SIX,
    SEVEN, EIGHT, NINE,
               ZERO,

// function
    F1, F2, F3,
    F4, F5, F6,
    F7, F8, F9,
    F10, F11, F12,

        LAST
    };

    bool get_key(Key key);
    bool get_key_down(Key key);
    bool get_key_up(Key key);
}
