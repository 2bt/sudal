#include "hero.hpp"
#include "world.hpp"


Hero::Hero(World& world, glm::vec2 const& pos) : Entity(world, pos) {
    m_world.set_hero(this);
    m_rect.size = { 8, 12 };
}


Hero::~Hero() {
    m_world.set_hero(nullptr);
}


void Hero::update() {
    if (m_input_state.dpad.x != 0) m_dir = m_input_state.dpad.x;

    m_vel.x = glm::clamp(m_input_state.dpad.x * 1.5f, m_vel.x - 0.25f, m_vel.x + 0.25f);

    // horizontal collision
    m_rect.pos.x += m_vel.x;
    float dx = m_world.collision(m_rect, Axis::X);
    if (dx != 0) {
        m_rect.pos.x += dx;
    }


    // jumping
    if (!m_in_air && m_input_state.jump && !m_old_input_state.jump) {
        m_vel.y -= 4;
        m_jump_control = true;
        m_in_air       = true;
    }
    if (m_in_air) {
        if (m_jump_control) {
            if (!m_input_state.jump && m_vel.y < -1) {
                m_vel.y = -1;
                m_jump_control = false;
            }
            if (m_vel.y > -1) m_jump_control = false;
        }
    }



    // gravity
    m_vel.y += 0.2;
    float vy = glm::clamp(m_vel.y, -3.0f, 3.0f);

    // vertical collision
    m_rect.pos.y += vy;
    float dy = m_world.collision(m_rect, Axis::Y, vy);
    if (dy != 0) {
        m_rect.pos.y += dy;
        m_vel.y = 0;
        if (dy < 0) {
            m_in_air = false;
        }
    }
    else {
        m_in_air = true;
    }

    m_old_input_state = m_input_state;
}


void Hero::draw(Camera const& camera) {
    auto pos = m_rect.pos - camera.get_rect().pos;
    SDL_Rect dst = {
        (int) std::floor(pos.x - 4 + 0.5f),
        (int) std::floor(pos.y - 4 + 0.5f),
        16, 16,
    };

    SDL_Rect src = { 0, 256, 16, 16 };
    gfx.render(TEX_TILES, src, dst, m_dir == -1);
//    SDL_SetRenderDrawColor(gfx.renderer(), 255, 0, 0, 255);
//    SDL_RenderFillRect(gfx.renderer(), &dst);
}
