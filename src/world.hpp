#pragma once
#include "entity.hpp"
#include "map.hpp"
#include "hero.hpp"
#include <vector>


class World {
public:
    bool init();
    void update();
    void draw();

    template<class T, class... Args>
    Entity& spawn_entity(Args&&... args) {
        auto e = std::make_unique<T>(*this, std::forward<Args>(args)...);
        m_new_entities.emplace_back(std::move(e));
        return *m_new_entities.back();
    }

    void set_hero(Hero* hero) { m_hero = hero; }
    Hero* get_hero() { return m_hero; }

private:
    std::vector<Entity::Ptr> m_entities;
    std::vector<Entity::Ptr> m_new_entities;

    Map    m_map;
    Camera m_camera;
    Hero*  m_hero = nullptr;
};
