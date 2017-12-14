#include "game.hpp"


bool Game::init() {
    if (!m_world.init()) return false;

    return true;
}


void Game::update() {
    Hero* hero = m_world.get_hero();
    if (hero) hero->set_input_state(m_input.get_state());

    m_world.update();
}


void Game::draw() {
    gfx.clear();

    m_world.draw();

    gfx.present();
}
