#pragma once
#include <memory>
#include <glm.hpp>
#include "camera.hpp"


class World;


class Entity {
public:
    using Ptr = std::unique_ptr<Entity>;

    Entity(World& world, Rect const& rect) : m_world(world), m_rect(rect) {}

    bool             is_alive()   const { return m_is_alive; }
    Rect const&      get_rect()   const { return m_rect; };
    glm::vec2        get_center() const { return m_rect.pos + m_rect.size * 0.5f; };
    glm::vec2 const& get_move()   const { return m_move; }
    void             die() { m_is_alive = false; }

    void set_move(glm::vec2 const& move) { m_move = move; }
    void apply_move(glm::vec2 const& move) { m_rect.pos += move; }

    virtual ~Entity() {}
    virtual void update() {}
    virtual void on_collision(Axis axis, float dist, Entity* other) {}
    virtual void draw(Camera const& camera);

protected:
    World& m_world;

private:
    bool      m_is_alive = true;
    Rect      m_rect     = { {}, { 16, 16 } };
    glm::vec2 m_move;
};


