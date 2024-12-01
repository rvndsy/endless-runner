#pragma once

#include <SFML/System/Vector2.hpp>
#include "Enemy.hpp"

class CrashedCar : public Enemy {
public:
    CrashedCar(float backgroundVelocity);
    ~CrashedCar() {};
    void update(float deltaTime, float backgroundVelocity) override;
    void update(float deltaTime) override { update(deltaTime, velocity.x); }; // WARN: Unsure...
};
