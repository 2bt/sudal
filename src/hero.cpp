#include "hero.hpp"


void Hero::update(Input::State const& input_state) {
    m_pos.x += input_state.dpad.x;
}

void Hero::draw() {
    SDL_Rect rect = { (int) m_pos.x - 4, (int) m_pos.y - 4, 8, 8 };
    SDL_SetRenderDrawColor(gfx.renderer(), 255, 0, 0, 255);
    SDL_RenderFillRect(gfx.renderer(), &rect);
}
