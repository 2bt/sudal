#include "world.hpp"
#include "hero.hpp"
#include "box.hpp"


bool World::init() {
    if (!m_map.load("res/map.txt")) return false;

    for (int y = 0; y < m_map.get_size().y; ++y)
    for (int x = 0; x < m_map.get_size().x; ++x) {
        char t = m_map.get_tile_at(x, y);
        glm::vec2 pos = { x * TILE_SIZE, y * TILE_SIZE };
        if (t == '@') spawn_entity<Hero>(pos);
        if (t == 'x') spawn_entity<Box>(pos);
    }

    return true;
}


void World::update() {

    // update entities
    for (auto it = m_entities.begin(); it != m_entities.end();) {
        (*it)->set_move({});
        (*it)->update();
        if (!(*it)->is_alive()) {
            it = m_entities.erase(it);
            continue;
        }
        ++it;
    }


    // horizontal collision
    for (Entity::Ptr& e : m_entities) {
        if (!e->is_alive()) continue;
        e->apply_move({ e->get_move().x, 0 });
        float dx = m_map.collision(e->get_rect(), Axis::X);
        if (dx != 0) e->on_collision(Axis::X, dx, nullptr);
        for (Entity::Ptr& e2 : m_entities) {
            if (!e2->is_alive()) continue;
            if (e == e2) continue;
            float dx = collision(e->get_rect(), e2->get_rect(), Axis::X);
            if (dx != 0) e->on_collision(Axis::X, dx, e2.get());
        }

    }

    // vertical collision
    for (Entity::Ptr& e : m_entities) {
        if (!e->is_alive()) continue;
        e->apply_move({ 0, e->get_move().y });
        float dy = m_map.collision(e->get_rect(), Axis::Y, e->get_move().y);
        if (dy != 0) e->on_collision(Axis::Y, dy, nullptr);
        for (Entity::Ptr& e2 : m_entities) {
            if (!e2->is_alive()) continue;
            if (e == e2) continue;
            float dy = collision(e->get_rect(), e2->get_rect(), Axis::Y);
            if (dy != 0) e->on_collision(Axis::Y, dy, e2.get());
        }
    }


    // append new entities
    m_entities.resize(m_entities.size() + m_new_entities.size());
    std::move(m_new_entities.begin(), m_new_entities.end(), m_entities.end() - m_new_entities.size());
    m_new_entities.clear();


    // camera
    if (m_hero) {
        Rect const& rect = m_hero->get_rect();
        m_camera.set_pos(rect.pos + rect.size * 0.5f);
    }
}


void World::draw() {

    m_map.draw(m_camera);

    for (Entity::Ptr& e : m_entities) {
        if (e->is_alive()) e->draw(m_camera);
    }
}
