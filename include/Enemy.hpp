#pragma once

#include "Definitions.hpp"
#include "Entity.hpp"

#define CRASHED_CAR_SPRITE SPRITE_DIR_PATH "crashed-car.png"
#define BIRD_SPRITE SPRITE_DIR_PATH "bird.png"

class Enemy : public Entity {
public:
    Enemy(sf::Vector2<float> position, sf::Vector2<float> velocity) : Entity(sf::Vector2<float>(position.x+WINDOW_WIDTH, position.y), velocity) {}; // GROUND_HEIGHT effectively becomes y = 0
    virtual ~Enemy() {return;};
    virtual void update(float deltaTime) = 0;
    virtual void update(float deltaTime, float backgroundVelocity) = 0;
};
