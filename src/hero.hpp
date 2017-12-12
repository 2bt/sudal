#pragma once
#include "map.hpp"
#include "input.hpp"


class Hero {
public:
    Hero(Map const& map) : m_map(map) {}

    void      update(Input::State const& input_state);
    void      set_pos(glm::vec2 const& pos) { m_rect.pos = pos - m_rect.size * 0.5f; }
    glm::vec2 get_pos() { return m_rect.pos + m_rect.size * 0.5f; }

    void      draw(Camera const& camera);

private:
    Rect       m_rect = { {}, { 12, 16 } };
    glm::vec2  m_vel;

    bool       m_in_air = true;

    Map const& m_map;
};
