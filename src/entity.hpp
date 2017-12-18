#pragma once
#include <memory>
#include <glm.hpp>
#include "camera.hpp"


class World;


class Entity {
public:
    using Ptr = std::unique_ptr<Entity>;

    Entity(World& world) : m_world(world) {}

    Rect const& get_rect() const { return m_rect; };
    bool        is_alive() const { return m_is_alive; }
    glm::vec2   get_center() const { return m_rect.pos + m_rect.size * 0.5f; };

    void        die() { m_is_alive = false; }


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


