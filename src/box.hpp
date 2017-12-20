#pragma once
#include "entity.hpp"


class Box : public Entity {
public:
    Box(World& world, glm::vec2 const& pos)
        : Entity(world, Rect::create_centered(pos, { 16, 16 }))
    {}

    void update() override {}
    void draw(Camera const& camera) override;

    void hit(int value) {
        m_energy -= value;
        if (m_energy <= 0) die();
    }

private:
    int m_energy = 3;
};

