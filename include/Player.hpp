#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../include/Entity.hpp"
#include "../include/Definitions.hpp"

// Player values
constexpr float PLAYER_START_X = 50.f;
constexpr float PLAYER_START_Y = GROUND_HEIGHT;
constexpr float PLAYER_CROUCHING_OFFSET_X = 0.f;
constexpr float PLAYER_CROUCHING_OFFSET_Y = 50.f;
constexpr float PLAYER_ASCENDING_OFFSET_X = 0.f;
constexpr float PLAYER_ASCENDING_OFFSET_Y = -12.f;
constexpr float PLAYER_FALLING_OFFSET_X = 0.f;
constexpr float PLAYER_FALLING_OFFSET_Y = -100.f;
// Player sprites
#define PLAYER_SPRITE SPRITE_DIR_PATH "player.png"
#define PLAYER_CROUCHING_SPRITE SPRITE_DIR_PATH "player-crouching.png"
#define PLAYER_ASCENDING_SPRITE SPRITE_DIR_PATH "player-ascending.png"
#define PLAYER_FALLING_SPRITE SPRITE_DIR_PATH "player-falling.png"

enum PlayerState { normal, crouching, jumping, falling };

class Player : public Entity {
public:
    Player(Vector2<float> position, Vector2<float> velocity);
    ~Player() {return;};
    void update(float deltaTime);
    void updateActiveSprite();
    //bool initSprite();
    //void setState(PlayerState state) {this->state = state;};
    //PlayerState getState() {return state;};
private:
    PlayerState state;
    Texture crouchingTexture;
    Sprite crouchingSprite;
    Texture jumpingTexture;
    Sprite jumpingSprite;
    Texture fallingTexture;
    Sprite fallingSprite;
};
