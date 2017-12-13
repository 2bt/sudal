#pragma once
#include "gfx.hpp"
#include <vector>
#include <string>


enum {
    TILE_SIZE = 16,
};

enum {
    TILE_WALL   = '0',
    TILE_BOARD  = '^',
    TILE_PLAYER = '@',
    TILE_BOX    = 'x',
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
        m_rect.pos = glm::floor(pos + glm::vec2(0.5, 0.5) - m_rect.size * 0.5f);
    }
private:
    Rect m_rect = { {}, { WIDTH, HEIGHT } };
};


class Map {
public:

    bool              load(const char* name);
    void              draw(Camera const& camera);

    char              get_tile_at(int x, int y) const;
    glm::ivec2 const& get_size() const { return m_size; }

    float collision(Rect const& rect, Axis axis, float vel = 0) const;

private:
    std::vector<std::string> m_data;
    glm::ivec2               m_size;
};
