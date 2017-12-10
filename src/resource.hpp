#pragma once
#include <array>
#include <SDL.h>


enum TextureID {
    TEX_FONT_MONO,
    TEX_FONT_SLIM,
    TEX_TILES,

    TEX_COUNT
};


enum FontID {
    FONT_MONO,
    FONT_SLIM,
};


struct FontSpec {
    TextureID           texture;
    int                 height;
    int                 width;
    std::array<int, 96> spacing;
};


struct Resource {
    static bool init();
    static void free();
    static SDL_Texture*     texture(TextureID tex);
    static FontSpec const & font_spec(FontID);
};
