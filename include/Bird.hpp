#pragma once

#include <SFML/System/Vector2.hpp>
#include "Enemy.hpp"

class Bird : public Enemy {
public:
    Bird(float height, float backgroundVelocity);
    ~Bird() {};
    void update(float deltaTime, float backgroundVelocity) override;
    void update(float deltaTime) override { update(deltaTime, velocity.x); }; // WARN: Unsure...
};
