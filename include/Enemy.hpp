#pragma once

#include "Definitions.hpp"
#include "Entity.hpp"

// Sprite file names
#define CRASHED_CAR_SPRITE SPRITE_DIR_PATH "crashed-car.png"
#define BIRD_SPRITE SPRITE_DIR_PATH "bird.png"
#define WALL_SPRITE SPRITE_DIR_PATH "wall.png"

class Enemy : public Entity {
public:
    // Enemy constructor also takes the sprite file name as a parameter
    Enemy(std::string spritePath, sf::Vector2f position, sf::Vector2f velocity);
    ~Enemy() {};    // unused
    // Enemies are synchronised with the background on update.
    virtual void update(float deltaTime, float backgroundVelocity) = 0;
    void update(float deltaTime) {};
protected:
    // One texture and sprite per enemy
    Texture defaultTexture;
    Sprite defaultSprite;
};
