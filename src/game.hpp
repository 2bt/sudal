#pragma once
#include "world.hpp"
#include "input.hpp"


class Player {
public:

private:

};


class Game {
public:
    bool init();
    void update();
    void draw();

    Input& get_input() { return m_input; }

private:

    World  m_world;

    Input  m_input;
};
