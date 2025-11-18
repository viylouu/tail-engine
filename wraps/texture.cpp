#include "texture.hpp"

namespace tail {
    Texture::Texture(const char* path) {
        ul = IMPL_fur_texture_load(path, { FUR_RENDER_API_GL });
    }

    Texture::~Texture() {
        IMPL_fur_texture_unload(ul, { FUR_RENDER_API_GL });
    }
}
