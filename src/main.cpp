#include <cstdio>
#include <cmath>
#include <cstdint>
#include <array>
#include "gfx.hpp"
#include "map.hpp"
#include "input.hpp"
#include "hero.hpp"


Input input;


class Game {
public:
    Game() : m_hero(m_map) {}
    bool init() {
        if (!m_map.load("res/map.txt")) return false;

        for (int y = 0; y < m_map.size().y; ++y)
        for (int x = 0; x < m_map.size().x; ++x) {
            char t = m_map.tile_at(x, y);
            if (t == '@') m_hero.set_pos(glm::vec2(x * 16, y * 16));
        }

        return true;
    }
    void update() {
        m_hero.update(input.get_state());
    }
    void draw() {
        m_map.draw();
        m_hero.draw();
    }

private:
    Map  m_map;
    Hero m_hero;
};


Game game;


int main(int argc, char** args) {
    if (!gfx.init()) return 1;

    game.init();

    SDL_Event e;
    bool running = true;
    while (running) {
        while (SDL_PollEvent(&e)) {

			switch (e.type) {
			case SDL_QUIT:
				running = false;
				break;

			case SDL_KEYDOWN:
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) running = false;
				break;

			case SDL_WINDOWEVENT:
				if (e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
                    gfx.resize(e.window.data1, e.window.data2);
				}
				break;


            case SDL_FINGERDOWN:
            case SDL_FINGERMOTION:
            case SDL_FINGERUP:
                input.event(e.type, e.tfinger.fingerId,
                            glm::ivec2(e.tfinger.x * WIDTH, e.tfinger.y * HEIGHT));
                break;

			default: break;
			}
        }


        game.update();

        gfx.clear();
        game.draw();

        gfx.set_font(FONT_SLIM);
        static int i = 0;
        gfx.printf({4, 4}, "Hello, world! %d", i++);

        gfx.present();
    }

    gfx.free();

    return 0;
}
