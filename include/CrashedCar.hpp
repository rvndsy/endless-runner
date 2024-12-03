#pragma once

#include <SFML/System/Vector2.hpp>
#include "Enemy.hpp"

// CrashedCar is on the ground and is static relative to the background
class CrashedCar : public Enemy {
public:
    CrashedCar(float backgroundVelocity) : Enemy(CRASHED_CAR_SPRITE, sf::Vector2f(0, 25.f), sf::Vector2f(backgroundVelocity, 0)) {};
    ~CrashedCar() {};
    // Update horizontal position synchronised with the background
    void update(float deltaTime, float backgroundVelocity) override;
};
