#pragma once

#include <core/data/texture.h>

namespace tail {
    struct Texture : FUR_texture {
        Texture(const char* path);
        ~Texture();
    };
}
