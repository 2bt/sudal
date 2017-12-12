#include "hero.hpp"


void Hero::update(Input::State const& input_state) {

    m_vel.x = input_state.dpad.x * 2;

    // horizontal collision
    m_rect.pos.x += m_vel.x;
    float dx = m_map.collision(m_rect, Axis::X);
    if (dx != 0) {
        m_rect.pos.x += dx;
    }


    // jumping
    if (!m_in_air && input_state.jump) {
        m_vel.y -= 5;
    }


    // gravity
    m_vel.y += 0.2;

    // vertical collision
    m_rect.pos.y += m_vel.y;
    float dy = m_map.collision(m_rect, Axis::Y);
    if (dy != 0) {
        m_rect.pos.y += dy;
        m_vel.y = 0;
        if (dy < 0) {
            m_in_air = false;
        }
    }
    else
    {
        m_in_air = true;
    }
}


void Hero::draw(Camera const& camera) {
    auto pos = m_rect.pos - camera.get_rect().pos;
    SDL_Rect r = {
        (int) pos.x,
        (int) pos.y,
        (int) m_rect.size.x,
        (int) m_rect.size.y,
    };
    SDL_SetRenderDrawColor(gfx.renderer(), 255, 0, 0, 255);
    SDL_RenderFillRect(gfx.renderer(), &r);
}
