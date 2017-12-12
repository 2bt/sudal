#include "map.hpp"
#include "gfx.hpp"


float collision(Rect const& a, Rect const& b, Axis axis) {
    if (a.pos.x >= b.pos.x + b.size.x
    || a.pos.y >= b.pos.y + b.size.y
    || a.pos.x + a.size.x <= b.pos.x
    || a.pos.y + a.size.y <= b.pos.y) return 0;
    auto s = b.pos + b.size - a.pos;
    auto t = b.pos - a.size - a.pos;
    if (axis == Axis::X) return std::abs(s.x) < std::abs(t.x) ? s.x : t.x;
    else                 return std::abs(s.y) < std::abs(t.y) ? s.y : t.y;
}


float Map::collision(Rect const& rect, Axis axis) const {

    int x1 = std::floor((rect.pos.x + TILE_SIZE / 2) / TILE_SIZE);
    int x2 = std::floor((rect.pos.x + rect.size.x + TILE_SIZE / 2) / TILE_SIZE);
    int y1 = std::floor((rect.pos.y + TILE_SIZE / 2) / TILE_SIZE);
    int y2 = std::floor((rect.pos.y + rect.size.y + TILE_SIZE / 2) / TILE_SIZE);


    Rect tile_rect;
    tile_rect.size = { TILE_SIZE, TILE_SIZE };

    float d = 0;

    for (int y = y1; y <= y2; ++y)
    for (int x = x1; x <= x2; ++x) {

        char t = get_tile_at(x, y);
        if (is_solid(t)) {

            tile_rect.pos.x = x * TILE_SIZE - TILE_SIZE / 2;
            tile_rect.pos.y = y * TILE_SIZE - TILE_SIZE / 2;
            float e = ::collision(rect, tile_rect, axis);
            if (std::abs(e) > std::abs(d)) d = e;

         }
    }

    return d;
}


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


char Map::get_tile_at(int x, int y) const {
    if (x < 0 || y < 0 ||
        y >= (int)m_data.size() ||
        x >= (int)m_data[y].size()) return '0';
    return m_data[y][x];
}


void Map::draw(Camera const& camera) {

    Rect const& rect = camera.get_rect();

    int x1 = std::floor(rect.pos.x / TILE_SIZE);
    int x2 = std::floor((rect.pos.x + rect.size.x) / TILE_SIZE);
    int y1 = std::floor(rect.pos.y / TILE_SIZE);
    int y2 = std::floor((rect.pos.y + rect.size.y) / TILE_SIZE);

    for (int y = y1; y <= y2; ++y)
    for (int x = x1; x <= x2; ++x) {

        int b = is_solid(get_tile_at(x, y)) * 1 +
                is_solid(get_tile_at(x + 1, y)) * 2 +
                is_solid(get_tile_at(x, y + 1)) * 4 +
                is_solid(get_tile_at(x + 1, y + 1)) * 8;

        SDL_Rect src = { 1 + b * (TILE_SIZE + 2), 1, TILE_SIZE, TILE_SIZE };
        SDL_Rect dst = {
            int(x * TILE_SIZE - rect.pos.x),
            int(y * TILE_SIZE - rect.pos.y),
            TILE_SIZE, TILE_SIZE
        };
        gfx.render(TEX_TILES, src, dst);
    }
}

