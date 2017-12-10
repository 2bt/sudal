#pragma once
#include <glm.hpp>
#include <SDL.h>

class Input {
public:

    struct State {
        glm::ivec2 dpad;
        bool       jump;
        bool       fire;
    };

    void event(uint32_t type, int id, glm::ivec2 const& pos);
    State get_state() const;


private:
    struct Touch {
        int        id = -1;
        glm::ivec2 pos;
        glm::ivec2 mov;
    };

    Touch m_touch;
};

