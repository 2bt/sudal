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

        for (int y = 0; y < m_map.get_size().y; ++y)
        for (int x = 0; x < m_map.get_size().x; ++x) {
            char t = m_map.get_tile_at(x, y);
            if (t == '@') m_hero.set_pos(glm::vec2(x * TILE_SIZE, y * TILE_SIZE));
        }

        return true;
    }
    void update() {
        m_hero.update(input.get_state());

        static glm::vec2 m_pos = m_hero.get_pos();
//        m_pos += (m_hero.get_pos() - m_pos) * 0.1f;

        auto p = m_hero.get_pos();
        if (m_pos.x < p.x) m_pos.x += 2;
        if (m_pos.x > p.x) m_pos.x -= 2;
        if (m_pos.y < p.y) m_pos.y += 2;
        if (m_pos.y > p.y) m_pos.y -= 2;

        m_camera.update(m_pos);
    }
    void draw() {
        m_map.draw(m_camera);
        m_hero.draw(m_camera);
    }

private:

    Map    m_map;
    Hero   m_hero;
    Camera m_camera;
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
                input.finger_down  (e.tfinger.fingerId, glm::ivec2(e.tfinger.x * WIDTH, e.tfinger.y * HEIGHT));
                break;
            case SDL_FINGERUP:
                input.finger_up    (e.tfinger.fingerId, glm::ivec2(e.tfinger.x * WIDTH, e.tfinger.y * HEIGHT));
                break;
            case SDL_FINGERMOTION:
                input.finger_motion(e.tfinger.fingerId, glm::ivec2(e.tfinger.x * WIDTH, e.tfinger.y * HEIGHT));
                break;

			default: break;
			}
        }


        game.update();

        gfx.clear();
        game.draw();

//        gfx.set_font(FONT_SLIM);
//        static int i = 0;
//        gfx.printf({4, 4}, "Hello, world! %d", i++);

        gfx.present();
    }

    gfx.free();

    return 0;
}
