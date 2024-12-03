#pragma once

#include <SFML/System/Vector2.hpp>
#include "Enemy.hpp"

// Wall is on the ground and is static relative to the background
class Wall : public Enemy {
public:
    Wall(float backgroundVelocity) : Enemy(WALL_SPRITE, sf::Vector2f(0, 0.f), sf::Vector2f(backgroundVelocity, 0)) {};
    ~Wall() {};
    // Update horizontal position synchronised with the background
    void update(float deltaTime, float backgroundVelocity) override;
};
