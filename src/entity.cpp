#include "entity.hpp"
#include "gfx.hpp"

void Entity::draw(Camera const& camera) {
    auto pos = m_rect.pos - camera.get_rect().pos;
    SDL_Rect dst = {
        (int) std::floor(pos.x + 0.5f),
        (int) std::floor(pos.y + 0.5f),
        (int) m_rect.size.x,
        (int) m_rect.size.y,
    };
    SDL_SetRenderDrawColor(gfx.get_renderer(), 255, 0, 0, 255);
    SDL_RenderFillRect(gfx.get_renderer(), &dst);
}
