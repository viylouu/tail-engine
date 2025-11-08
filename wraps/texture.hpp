#pragma once

#include <core/data/texture.h>

namespace tail {
    struct Texture {
        FUR_texture* tex;

        Texture(const char* path);
        ~Texture();
    };
}
