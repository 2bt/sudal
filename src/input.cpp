#include "input.hpp"
#include "gfx.hpp"


void Input::finger_down(int id, glm::ivec2 const& pos) {
    int index = TOUCH_DPAD;
    if      (pos.x > WIDTH - 40) index = TOUCH_JUMP;
    else if (pos.x > WIDTH - 80) index = TOUCH_FIRE;

    Touch& t = m_touches[index];
    if (t.id != -1) return;
    t.id = id;
    t.pos = pos;
}


void Input::finger_up(int id, glm::ivec2 const& pos) {
    if (Touch* t = get_touch(id)) {
        t->id = -1;
        t->mov = {};
    }
}


void Input::finger_motion(int id, glm::ivec2 const& pos) {
    if (Touch* t = get_touch(id)) {
        t->mov += pos - t->pos;
        t->mov = glm::clamp(t->mov, glm::ivec2(-5, -5), glm::ivec2(5, 5));
        t->pos = pos;
    }
}


Input::State Input::get_state() const {
    State s = {};

    // touch
    glm::ivec2 const& dpad = m_touches[TOUCH_DPAD].mov;
    s.dpad.x = (dpad.x > 2) - (dpad.x < -2);
    s.dpad.y = (dpad.y > 2) - (dpad.y < -2);
    s.jump = m_touches[TOUCH_JUMP].id != -1;
    s.fire = m_touches[TOUCH_FIRE].id != -1;

    // keyboard
    const Uint8* ks = SDL_GetKeyboardState(nullptr);
    s.dpad.x += !!ks[SDL_SCANCODE_RIGHT] - !!ks[SDL_SCANCODE_LEFT];
    s.dpad.y += !!ks[SDL_SCANCODE_DOWN] - !!ks[SDL_SCANCODE_UP];
    s.jump |= !!ks[SDL_SCANCODE_X];
    s.fire |= !!ks[SDL_SCANCODE_C];

    return s;
}
