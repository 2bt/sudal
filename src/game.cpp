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

//    SDL_SetRenderDrawColor(gfx.get_renderer(), 255, 0, 0, 255);
//    SDL_RenderDrawLine(gfx.get_renderer(),
//                       WIDTH - 40, 0,
//                       WIDTH - 40, HEIGHT);
//    SDL_RenderDrawLine(gfx.get_renderer(),
//                       WIDTH - 80, 0,
//                       WIDTH - 80, HEIGHT);

    gfx.present();
}
