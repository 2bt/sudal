#pragma once
#include "entity.hpp"
#include "input.hpp"


class Laser : public Entity {
public:
    Laser(World& world, glm::vec2 const& pos, int dir);

    void update() override;
    void draw(Camera const& camera) override;

private:
    int m_dir;
};



class Hero : public Entity {
public:
    Hero(World& world, glm::vec2 const& pos);
    ~Hero();

    void update() override;
    void draw(Camera const& camera) override;
    void set_input_state(Input::State state) { m_input_state = state; }

private:
    glm::vec2    m_vel;
    int          m_dir          = 1;
    bool         m_in_air       = true;
    bool         m_jump_control = false;
    int          m_shoot_delay  = 0;

    Input::State m_input_state;
    Input::State m_old_input_state;
};
