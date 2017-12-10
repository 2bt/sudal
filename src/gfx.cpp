#include "gfx.hpp"
#include "resource.hpp"
#include <cstdarg>



bool Gfx::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    m_window = SDL_CreateWindow("sudal",
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                WIDTH * 4, HEIGHT * 4,
                                SDL_WINDOW_RESIZABLE);
    if (!m_window) {
        SDL_Log("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1,
                                    SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!m_renderer) {
        SDL_Log("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_RenderSetLogicalSize(m_renderer, WIDTH, HEIGHT);

    if (!Resource::init()) return false;

    return true;
}


void Gfx::free() {
    Resource::free();
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}


void Gfx::clear() {
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(m_renderer, nullptr);
}


void Gfx::render(TextureID tex, SDL_Rect const& src, SDL_Rect const& dst) const {
    SDL_RenderCopy(gfx.renderer(), Resource::texture(tex), &src, &dst);
}


void Gfx::print(glm::ivec2 const& pos, char const* str) const {
    FontSpec const & spec = Resource::font_spec(m_font);
    SDL_Rect src = { 0, 0, 0, spec.height };
    SDL_Rect dst = { pos.x, pos.y, 0, spec.height };
    int c;
    while ((c = *str++)) {
        if (c == '\n') {
            dst.x = pos.x;
            dst.y += spec.height;
            continue;
        }
        int i = glm::clamp(c - 32, 0, 95);
        src.w = dst.w = spec.spacing[i];
        src.x = i % 16 * spec.width;
        src.y = i / 16 * spec.height;
        gfx.render(spec.texture, src, dst);
        dst.x += dst.w;
    }
}


void Gfx::printf(glm::ivec2 const& pos, char const* fmt, ...) const {
    va_list args;
    va_start(args, fmt);
    char line[256] = {};
    vsnprintf(line, 256, fmt, args);
    va_end(args);
    print(pos, line);
}


Gfx gfx;
