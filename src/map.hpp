#pragma once

#include "gfx.hpp"
#include <vector>
#include <string>


class Map {
public:

    bool load(const char* name);
    char tile_at(int x, int y) const;
    void draw();

    static bool is_solid(char c) { return c == '0'; }
    glm::ivec2 const& size() const { return m_size; }

private:
    std::vector<std::string> m_data;
    glm::ivec2               m_size;
};

