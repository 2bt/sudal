#pragma once
#include "map.hpp"
#include "input.hpp"

class Hero {
public:
    Hero(Map const& map) : m_map(map) {}

    void update(Input::State const& input_state);
    void set_pos(glm::vec2 const& pos) { m_pos = pos; }
    void draw();

private:
    glm::vec2  m_pos;
    Map const& m_map;
};

