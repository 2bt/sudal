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

    SDL_SetRenderDrawColor(gfx.get_renderer(), 255, 0, 0, 100);

    SDL_SetRenderDrawBlendMode(gfx.get_renderer(), SDL_BLENDMODE_BLEND);

    SDL_Rect rect = { WIDTH - 80, HEIGHT - 40, 39, 39 };
    SDL_RenderFillRect(gfx.get_renderer(), &rect);
    rect.x += 40;
    SDL_RenderFillRect(gfx.get_renderer(), &rect);

    gfx.print({ WIDTH - 77, HEIGHT - 12 }, "fire");
    gfx.print({ WIDTH - 37, HEIGHT - 12 }, "jump");

//    SDL_RenderDrawLine(gfx.get_renderer(),
//                       WIDTH - 40, HEIGHT - 40,
//                       WIDTH - 40, HEIGHT);
//    SDL_RenderDrawLine(gfx.get_renderer(),
//                       WIDTH - 80, HEIGHT - 40,
//                       WIDTH - 80, HEIGHT);
//    SDL_RenderDrawLine(gfx.get_renderer(),
//                       WIDTH - 80, HEIGHT - 40,
//                       WIDTH,      HEIGHT - 40);
//    SDL_RenderDrawLine(gfx.get_renderer(),
//                       WIDTH - 80, HEIGHT - 1,
//                       WIDTH,      HEIGHT - 1);

    gfx.present();
}
