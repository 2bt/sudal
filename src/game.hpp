#pragma once
#include "map.hpp"
#include "hero.hpp"
#include "input.hpp"



class Game {
public:
    Game();
    bool init();
    void update();
    void draw();

    Input& get_input() { return m_input; }

private:

    Map    m_map;
    Hero   m_hero;
    Camera m_camera;
    Input  m_input;
};
