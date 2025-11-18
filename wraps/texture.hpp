#pragma once

#include <core/data/texture.h>

namespace tail {
    class Texture {
public:
        FUR_texture* ul;
public:
        Texture(const char* path);
        ~Texture();
    };
}
