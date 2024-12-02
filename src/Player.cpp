#include <SFML/Graphics.hpp>
#include "../include/Definitions.hpp"
#include "../include/Player.hpp"

using namespace sf;
Player::Player(Vector2f position, Vector2f velocity) : Entity(position, velocity) {
    sprites.resize(4);
    textures.resize(4);
    // Loading player texture files
    if (!textures[normal].loadFromFile(PLAYER_SPRITE)) {
        throw std::runtime_error("Player - defaultTexture.loadFromFile: Error reading loading sprite file!\n");
    }
    if (!textures[crouching].loadFromFile(PLAYER_CROUCHING_SPRITE)) {
        throw std::runtime_error("Player - crouchingTexture.loadFromFile: Error loading sprite file!\n");
    }
    if (!textures[ascending].loadFromFile(PLAYER_ASCENDING_SPRITE)) {
        throw std::runtime_error("Player - jumpingTexture.loadFromFile: Error loading sprite file!\n");
    }
    if (!textures[falling].loadFromFile(PLAYER_FALLING_SPRITE)) {
        throw std::runtime_error("Player - fallingTexture.loadFromFile: Error loading sprite file!\n");
    }
    // Setting up sprites from textures
    for (size_t i = 0; i < sprites.size(); i++) {
        sprites[i].setTexture(textures[i]);
        sprites[i].setScale(SPRITE_SCALING, SPRITE_SCALING);
    }
    // Setting origin to middle of each sprite with the exception of: sprites[falling] being 6 px taller and sprites[crouching] being much wider and shorter
    sprites[normal].setOrigin(sprites[normal].getLocalBounds().width / 2, sprites[normal].getLocalBounds().height / 2);
    sprites[crouching].setOrigin(sprites[crouching].getLocalBounds().width / 2 - 8.f, sprites[crouching].getLocalBounds().height / 2 - 11.f);
    sprites[ascending].setOrigin(sprites[ascending].getLocalBounds().width / 2, sprites[ascending].getLocalBounds().height / 2);
    sprites[falling].setOrigin(sprites[falling].getLocalBounds().width / 2, sprites[falling].getLocalBounds().height / 2 + 3.f);
    // Setting defaul player state
    switchState(normal);
}

// Update states according to Keyboard events or the current velocity (y axis is flipped)
void Player::update(float deltatime) {
    // Push the player down if midair and S is pressed
    if (Keyboard::isKeyPressed(Keyboard::S) && position.y < GROUND_HEIGHT) {
        switchState(crouching);
        acceleration.y = PUSH_DOWN_FORCE;
        return;
    }
    acceleration.y = 0.f;
    // If player is going down the player is falling
    if (velocity.y > 0) {
        switchState(falling);
        return;
    // If player is going up the player is ascending
    } else if (velocity.y < 0) {
        switchState(ascending);
        return;
    }
    // If the player is on the ground and S is pressed - crouch
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        switchState(crouching);
        return;
    // If the player is on the ground and W is pressed - jump
    } else if (Keyboard::isKeyPressed(Keyboard::W)) {
        jump();
        return;
    }
    // Otherwise when nothing is happening - normal
    switchState(normal);
}
// Switch state and update appropriate sprite
void Player::switchState(PlayerState state) {
    this->state = state;
    activeSprite = &sprites[state];
}
// Make the player jump by giving it vertical speed if it isnt touching the ground (y axis is flipped)
void Player::jump() {
    switchState(ascending);
    if (position.y >= GROUND_HEIGHT) {
        acceleration.y = 0.f;
        velocity.y = JUMP_VELOCITY;
    }
}
