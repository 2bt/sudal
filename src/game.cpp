#include "game.hpp"


Game::Game() : m_hero(m_map) {}


bool Game::init() {
    if (!m_map.load("res/map.txt")) return false;

    for (int y = 0; y < m_map.get_size().y; ++y)
    for (int x = 0; x < m_map.get_size().x; ++x) {
        char t = m_map.get_tile_at(x, y);
        if (t == '@') m_hero.set_pos(glm::vec2(x * TILE_SIZE, y * TILE_SIZE));
    }

    return true;
}


void Game::update() {
    m_hero.update(m_input.get_state());

    m_camera.update(m_hero.get_pos());
}


void Game::draw() {
    m_map.draw(m_camera);
    m_hero.draw(m_camera);
}
