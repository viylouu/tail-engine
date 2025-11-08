#include "texture.hpp"

#include <cstdlib>
#include <nouser/state.hpp>

namespace tail {
    Texture::Texture(const char* path) {
        tex = IMPL_fur_texture_load(path, OP_fur_texture_GENERIC{ .api = FUR_RENDER_API_GL });
    }

    Texture::~Texture() {
        IMPL_fur_texture_unload(tex, OP_fur_texture_GENERIC{ .api = FUR_RENDER_API_GL });
    }
}
