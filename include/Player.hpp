#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include "../include/Entity.hpp"
#include "../include/Definitions.hpp"

// Player sprite values
constexpr float PLAYER_START_X = 50.f;
constexpr float PLAYER_START_Y = GROUND_HEIGHT;
constexpr float PLAYER_CROUCHING_OFFSET_X = 0.f;
constexpr float PLAYER_CROUCHING_OFFSET_Y = 50.f;
constexpr float PLAYER_ASCENDING_OFFSET_X = 0.f;
constexpr float PLAYER_ASCENDING_OFFSET_Y = -12.f;
constexpr float PLAYER_FALLING_OFFSET_X = 0.f;
constexpr float PLAYER_FALLING_OFFSET_Y = -100.f;
// Player physics values
constexpr float JUMP_VELOCITY = -700.f; //y axis is flipped
constexpr float PUSH_DOWN_FORCE = 30.f;
// Player sprites
#define PLAYER_SPRITE SPRITE_DIR_PATH "player.png"
#define PLAYER_CROUCHING_SPRITE SPRITE_DIR_PATH "player-crouching.png"
#define PLAYER_ASCENDING_SPRITE SPRITE_DIR_PATH "player-ascending.png"
#define PLAYER_FALLING_SPRITE SPRITE_DIR_PATH "player-falling.png"

enum PlayerState { normal = 0, crouching = 1, ascending = 2, falling = 3 };

class Player : public Entity {
public:
    Player(Vector2f position, Vector2f velocity);
    ~Player() {};
    void update(float deltaTime) override;
    void update(float deltaTime, float backgroundVelocity) override { update(deltaTime); };
    Sprite getSprite() override {return sprites[state];};
    void updateActiveSprite();
private:
    // TODO: Store these in a vector/array where the index is the value of enum of the sprite
    PlayerState state;
    std::vector<Texture> textures;
    std::vector<Sprite> sprites;
    void switchState(PlayerState);
    void jump();
    void pushDown();
};
