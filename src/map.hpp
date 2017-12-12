#pragma once
#include "gfx.hpp"
#include <vector>
#include <string>


enum {
    TILE_SIZE = 16,
};


struct Rect {
    glm::vec2 pos;
    glm::vec2 size;
};


enum class Axis { X, Y };


class Camera {
public:
    Rect const& get_rect() const { return m_rect; }
    void update(glm::vec2 const& pos) {
        m_rect.pos = pos - m_rect.size * 0.5f;
    }
private:
    Rect m_rect = { {}, { WIDTH, HEIGHT } };
};


class Map {
public:

    bool              load(const char* name);
    void              draw(Camera const& camera);

    static bool       is_solid(char c) { return c == '0'; }
    char              get_tile_at(int x, int y) const;
    glm::ivec2 const& get_size() const { return m_size; }

    float collision(Rect const& rect, Axis axis) const;

private:
    std::vector<std::string> m_data;
    glm::ivec2               m_size;
};
