#include "resource.hpp"
#include "gfx.hpp"
#include <SDL_image.h>


namespace {


constexpr FontSpec font_specs[] = {
    {
        TEX_FONT_MONO, 8, 8, {
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
            8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,
        }
    },
    {
        TEX_FONT_SLIM, 12, 8, {
            2, 2, 2, 7, 6, 8, 6, 2, 4, 4, 6, 6, 2, 5, 2, 4,
            6, 3, 6, 5, 6, 6, 6, 6, 6, 6, 2, 2, 5, 5, 5, 5,
            8, 6, 6, 5, 6, 5, 5, 6, 6, 2, 6, 6, 6, 6, 6, 6,
            6, 7, 6, 6, 6, 6, 6, 6, 6, 6, 6, 4, 4, 4, 6, 5,
            3, 5, 5, 4, 5, 5, 5, 5, 5, 2, 4, 5, 2, 6, 5, 5,
            5, 5, 5, 5, 5, 5, 6, 6, 6, 5, 6, 5, 2, 5, 7, 2,
        }
    }
};


std::array<SDL_Texture*, TEX_COUNT> textures;


SDL_Texture* load_texture(char const* name) {
    SDL_Surface* img = IMG_Load(name);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(gfx.get_renderer(), img);
    SDL_FreeSurface(img);
    return tex;
}


} // namespace


bool Resource::init() {
    if (!(textures[TEX_FONT_MONO] = load_texture("res/font-mono.png")) ||
        !(textures[TEX_FONT_SLIM] = load_texture("res/font-slim.png")) ||
        !(textures[TEX_TILES]     = load_texture("res/tiles.png"))) return false;
    return true;
}


void Resource::free() {
    for (auto &tex : textures) {
        SDL_DestroyTexture(tex);
        tex = nullptr;
    }
}


SDL_Texture*     Resource::texture(TextureID tex) { return textures[tex]; }
FontSpec const & Resource::font_spec(FontID font) { return font_specs[font]; }
