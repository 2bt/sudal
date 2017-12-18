#include "box.hpp"
#include "gfx.hpp"
#include "map.hpp"


void Box::draw(Camera const& camera) {
    auto pos = m_rect.pos - camera.get_rect().pos;
    SDL_Rect dst = {
        (int) std::floor(pos.x + 0.5f),
        (int) std::floor(pos.y + 0.5f),
        16, 16,
    };
    SDL_Rect src = { 0, 280, TILE_SIZE, TILE_SIZE };
    gfx.render(TEX_TILES, src, dst);
}
