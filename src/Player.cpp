#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <iostream>
#include "../include/Player.hpp"

Player::Player(sf::Vector2<float> position, sf::Vector2<float> velocity) : Entity(position, velocity) {
    Entity::initSprite(PLAYER_SPRITE);
    defaultSprite.setPosition(this->position.x, this->position.y);
    defaultSprite.setScale(SPRITE_SCALING, SPRITE_SCALING);

    crouchingTexture.loadFromFile(PLAYER_CROUCHING_SPRITE);
    crouchingSprite.setTexture(crouchingTexture);
    crouchingSprite.setScale(SPRITE_SCALING, SPRITE_SCALING);

    jumpingTexture.loadFromFile(PLAYER_ASCENDING_SPRITE);
    jumpingSprite.setTexture(jumpingTexture);
    jumpingSprite.setScale(SPRITE_SCALING, SPRITE_SCALING);

    fallingTexture.loadFromFile(PLAYER_FALLING_SPRITE);
    fallingSprite.setTexture(fallingTexture);
    fallingSprite.setScale(SPRITE_SCALING, SPRITE_SCALING);

    // Setting origin to middle of each sprite with the exception of fallingSprite, it is 6 pixels taller and crouching is much wider and shorter
    defaultSprite.setOrigin(defaultSprite.getLocalBounds().width / 2, defaultSprite.getLocalBounds().height / 2);
    crouchingSprite.setOrigin(crouchingSprite.getLocalBounds().width / 2 - 8.f, crouchingSprite.getLocalBounds().height / 2 - 11.f);
    jumpingSprite.setOrigin(jumpingSprite.getLocalBounds().width / 2, jumpingSprite.getLocalBounds().height / 2);
    fallingSprite.setOrigin(fallingSprite.getLocalBounds().width / 2, fallingSprite.getLocalBounds().height / 2 + 3.f);

    state = normal;
}

// TODO: Find a way to control keypresses with polling in Game class and not check assign activeSprite every update()
void Player::update(float deltatime) {
    if (velocity.y > 0) {
        state = falling;
        activeSprite = &fallingSprite;
        return;
    } else if (velocity.y < 0) {
        state = jumping;
        activeSprite = &jumpingSprite;
        return;
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        //std::cout << "Crouch!" << std::endl;
        state = crouching;
        activeSprite = &crouchingSprite;
    } else if (Keyboard::isKeyPressed(Keyboard::W)) {
        //std::cout << "Jump!" << std::endl;
        state = jumping;
        activeSprite = &jumpingSprite;
        if (position.y >= GROUND_HEIGHT) {
            velocity.y = -700.f;
        }
    } else {
        //std::cout << "Return to normal" << std::endl;
        state = normal;
        activeSprite = &defaultSprite;
    }
}
