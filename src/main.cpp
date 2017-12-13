#include <cstdio>
#include <cmath>
#include <cstdint>
#include <array>
#include "game.hpp"


int main(int argc, char** args) {
    if (!gfx.init()) return 1;

    Game game;
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
                game.get_input().finger_down  (e.tfinger.fingerId, glm::ivec2(e.tfinger.x * WIDTH, e.tfinger.y * HEIGHT));
                break;
            case SDL_FINGERUP:
                game.get_input().finger_up    (e.tfinger.fingerId, glm::ivec2(e.tfinger.x * WIDTH, e.tfinger.y * HEIGHT));
                break;
            case SDL_FINGERMOTION:
                game.get_input().finger_motion(e.tfinger.fingerId, glm::ivec2(e.tfinger.x * WIDTH, e.tfinger.y * HEIGHT));
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
