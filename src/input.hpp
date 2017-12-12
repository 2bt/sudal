#pragma once
#include <array>
#include <glm.hpp>
#include <SDL.h>


class Input {
public:

    struct State {
        glm::ivec2 dpad;
        bool       jump;
        bool       fire;
    };

    void finger_down(int id, glm::ivec2 const& pos);
    void finger_up(int id, glm::ivec2 const& pos);
    void finger_motion(int id, glm::ivec2 const& pos);

    State get_state() const;


private:
    struct Touch {
        int        id = -1;
        glm::ivec2 pos;
        glm::ivec2 mov;
    };

    enum {
        TOUCH_DPAD,
        TOUCH_JUMP,
        TOUCH_FIRE,

        TOUCH_COUNT
    };

    std::array<Touch, TOUCH_COUNT> m_touches;

    Touch* get_touch(int id) {
        for(Touch& t : m_touches) if (t.id == id) return &t;
        return nullptr;
    };
};

