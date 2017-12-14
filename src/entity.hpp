#pragma once
#include <memory>
#include <glm.hpp>
#include "camera.hpp"


class World;


class Entity {
public:
    using Ptr = std::unique_ptr<Entity>;

    Entity(World& world, glm::vec2 const& pos)
        : m_world(world)
    {
        m_rect.pos = pos - m_rect.size * 0.5f;
    }

    Rect const& get_rect() const { return m_rect; };
    bool is_alive() const { return m_is_alive; }
    void die() { m_is_alive = false; }

    virtual ~Entity() {}
    virtual void update() {}
    virtual void draw(Camera const& camera);

//    virtual void on_collision(Entity& other) {}

protected:
    World& m_world;
    Rect   m_rect = { {}, { 16, 16 } };

private:
    bool   m_is_alive = true;
};


