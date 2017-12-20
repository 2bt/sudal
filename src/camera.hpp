#pragma once
#include <glm.hpp>


enum class Axis { X, Y };


struct Rect {
    glm::vec2 pos;
    glm::vec2 size;

    static Rect create_centered(glm::vec2 const& center, glm::vec2 const& size) {
        return { center - size * 0.5f, size };
    }
};


class Camera {
public:
    Camera();

    Rect const& get_rect() const { return m_rect; }
    void set_pos(glm::vec2 const& pos) {
        m_rect.pos = glm::floor(pos + glm::vec2(0.5, 0.5) - m_rect.size * 0.5f);
    }
private:
    Rect m_rect;
};
