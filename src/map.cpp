#include "map.hpp"
#include "gfx.hpp"


bool Map::load(const char* name) {
    SDL_RWops* f = SDL_RWFromFile(name, "r");
    if (!f) return false;
    std::vector<char> raw(SDL_RWsize(f));
    SDL_RWread(f, &raw[0], 1, raw.size());
    SDL_RWclose(f);
    m_data.clear();
    m_size = {};
    int pos = 0;
    for (int i = 0; i < (int) raw.size(); ++i) {
        if (raw[i] == '\n') {
            m_data.push_back(std::string(&raw[0] + pos, i - pos));
            m_size.x = std::max(m_size.x, (int) m_data.back().size());
            pos = i + 1;
        }
    }
    m_size.y = (int) m_data.size();
    return true;
}


char Map::tile_at(int x, int y) const {
    if (x < 0 || y < 0 ||
        y >= (int)m_data.size() ||
        x >= (int)m_data[y].size()) return '0';
    return m_data[y][x];
}


void Map::draw() {
    for (int y = 0; y < 13; ++y)
    for (int x = 0; x < 21; ++x) {
        int b = is_solid(tile_at(x, y)) * 1 +
                is_solid(tile_at(x + 1, y)) * 2 +
                is_solid(tile_at(x, y + 1)) * 4 +
                is_solid(tile_at(x + 1, y + 1)) * 8;

        SDL_Rect src = { 1 + b * 18, 1, 16, 16 };
        SDL_Rect dst = { x * 16, y * 16, 16, 16 };
        gfx.render(TEX_TILES, src, dst);
    }
}

