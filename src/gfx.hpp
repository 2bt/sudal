#pragma once
#include "resource.hpp"
#include <SDL.h>
#include <array>
#include <memory>
#include <glm.hpp>


enum {
    WIDTH  = 320,
    HEIGHT = 180,
};


class Gfx {
public:
    bool init();
    void free();
    void resize(int w, int h) {}
    void present() { SDL_RenderPresent(m_renderer); }
    void clear();
    void render(TextureID tex, SDL_Rect const& src, SDL_Rect const& dst, int flip=0) const;

    SDL_Renderer* renderer() const { return m_renderer; }

    void set_font(FontID font) { m_font = font; }
    void print(glm::ivec2 const& pos, char const* str) const;
    void printf(glm::ivec2 const& pos, char const* fmt, ...) const;

private:

    SDL_Window*   m_window   = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    FontID        m_font     = FONT_MONO;
};

extern Gfx gfx;
