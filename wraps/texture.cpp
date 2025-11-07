#include "texture.hpp"

#include <cstdlib>
#include <nouser/state.hpp>

namespace tail {
    Texture::Texture(const char* path) {
        FUR_texture* tex = IMPL_fur_texture_load(path, OP_fur_texture_GENERIC{ .api = FUR_RENDER_API_GL });
        spec = tex->spec;
        width = tex->width;
        height = tex->height;
        free(tex);
    }

    Texture::~Texture() {
        IMPL_fur_texture_unload(this, OP_fur_texture_GENERIC{ .api = FUR_RENDER_API_GL });
    }
}
