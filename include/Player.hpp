#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include "../include/Entity.hpp"
#include "../include/Definitions.hpp"

// Player sprite values
constexpr float PLAYER_START_X = 50.f;
constexpr float PLAYER_START_Y = GROUND_HEIGHT;
// Player physics values
constexpr float JUMP_VELOCITY = -700.f; //y axis is flipped
constexpr float PUSH_DOWN_FORCE = 30.f;
// Player sprites
#define PLAYER_SPRITE SPRITE_DIR_PATH "player.png"
#define PLAYER_CROUCHING_SPRITE SPRITE_DIR_PATH "player-crouching.png"
#define PLAYER_ASCENDING_SPRITE SPRITE_DIR_PATH "player-ascending.png"
#define PLAYER_FALLING_SPRITE SPRITE_DIR_PATH "player-falling.png"

// Player has 4 states
enum PlayerState { normal = 0, crouching = 1, ascending = 2, falling = 3 };

class Player : public Entity {
public:
    Player(Vector2f position, Vector2f velocity);
    ~Player() {}; //empty implementation
    // Update player values
    void update(float deltaTime) override;

    void update(float deltaTime, float backgroundVelocity) override { update(deltaTime); }; //not used for Player
private:
    // Store all textures and sprites in an array where the index of the sprite is the state it belongs to
    std::vector<Texture> textures;
    std::vector<Sprite> sprites;

    // Track the current player state
    PlayerState state;
    // Switch the state in one function
    void switchState(PlayerState);

    // Make the player jump!
    void jump();
};
