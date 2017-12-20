#include "box.hpp"
#include "gfx.hpp"
#include "map.hpp"


void Box::draw(Camera const& camera) {
    auto pos = get_rect().pos - camera.get_rect().pos;
    SDL_Rect dst = {
        (int) std::floor(pos.x + 0.5f),
        (int) std::floor(pos.y + 0.5f),
        16, 16,
    };
    SDL_Rect src = { (3 - m_energy) * 16, 280, TILE_SIZE, TILE_SIZE };
    gfx.render(TEX_TILES, src, dst);
}
