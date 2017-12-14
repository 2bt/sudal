#include "world.hpp"
#include "hero.hpp"


bool World::init() {
    if (!m_map.load("res/map.txt")) return false;

    for (int y = 0; y < m_map.get_size().y; ++y)
    for (int x = 0; x < m_map.get_size().x; ++x) {
        char t = m_map.get_tile_at(x, y);
        glm::vec2 pos = { x * TILE_SIZE, y * TILE_SIZE };
        if (t == '@') spawn_entity<Hero>(pos);
    }

    return true;
}


void World::update() {

    // update entities
    for (auto it = m_entities.begin(); it != m_entities.end();) {
        (*it)->update();
        if (!(*it)->is_alive()) {
            it = m_entities.erase(it);
            continue;
        }
        ++it;
    }

    if (m_hero) {
        Rect const& rect = m_hero->get_rect();
        m_camera.set_pos(rect.pos + rect.size * 0.5f);
    }

    // append new entities
    m_entities.resize(m_entities.size() + m_new_entities.size());
    std::move(m_new_entities.begin(), m_new_entities.end(), m_entities.end() - m_new_entities.size());
    m_new_entities.clear();
}


void World::draw() {

    m_map.draw(m_camera);

    for (Entity::Ptr& e : m_entities) {
        if (e->is_alive()) e->draw(m_camera);
    }
}
