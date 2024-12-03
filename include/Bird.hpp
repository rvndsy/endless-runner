#pragma once

#include <SFML/System/Vector2.hpp>
#include "Enemy.hpp"

class Bird : public Enemy {
public:
    // Bird constructor adds extra velocity relative to the background
    Bird(float backgroundVelocity, float height) : Enemy(BIRD_SPRITE, sf::Vector2f(0, height), sf::Vector2f(backgroundVelocity+10.f, 0)) {};
    ~Bird() {};
    // Update bird horizontal position
    void update(float deltaTime, float backgroundVelocity) override;
};
