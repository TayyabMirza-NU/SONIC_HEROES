// Enemy.hpp
#pragma once
#include "Utilities.h"
#include "Animation.h"

class Enemy {
protected:
    int health{ 100 };
    int damage{ 10 };
public:
    Hitbox hitbox;
    Animation anim;
    virtual ~Enemy() = default;
    virtual void takeDamage(int amount) { health -= amount; }
    virtual void aiUpdate(float dt) = 0;
    virtual void patrol() = 0;
};