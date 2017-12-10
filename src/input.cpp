#include "input.hpp"


void Input::event(uint32_t type, int id, glm::ivec2 const& pos) {
    if (type == SDL_FINGERDOWN) {
        if (m_touch.id != -1) return;
        m_touch.id = id;
        m_touch.pos = pos;
    }
    if (type == SDL_FINGERUP) {
        if (m_touch.id != id) return;
        m_touch.id = -1;
        m_touch.mov = {};
    }
    if (type == SDL_FINGERMOTION) {
        if (m_touch.id != id) return;
        m_touch.mov += pos - m_touch.pos;
        m_touch.mov = glm::clamp(m_touch.mov, glm::ivec2(-5, -5), glm::ivec2(5, 5));
        m_touch.pos = pos;
    }
}


Input::State Input::get_state() const {
    State s = {};
    s.dpad.x = (m_touch.mov.x > 2) - (m_touch.mov.x < -2);
    s.dpad.y = (m_touch.mov.y > 2) - (m_touch.mov.y < -2);

    const Uint8* ks = SDL_GetKeyboardState(nullptr);
    s.dpad.x = !!ks[SDL_SCANCODE_RIGHT] - !!ks[SDL_SCANCODE_LEFT];
    s.dpad.y = !!ks[SDL_SCANCODE_UP] - !!ks[SDL_SCANCODE_DOWN];

    return s;
}
