#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstdlib>
#include <iostream>
#include "../include/Player.hpp"

Player::Player(sf::Vector2<float> position, sf::Vector2<float> velocity) : Entity(position, velocity) {
    sprites.resize(4);
    textures.resize(4);
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

    for (size_t i = 0; i < sprites.size(); i++) {
        sprites[i].setTexture(textures[i]);
        sprites[i].setScale(SPRITE_SCALING, SPRITE_SCALING);
    }

    // Setting origin to middle of each sprite with the exception of sprites[falling], it is 6 pixels taller and crouching is much wider and shorter
    sprites[normal].setOrigin(sprites[normal].getLocalBounds().width / 2, sprites[normal].getLocalBounds().height / 2);
    sprites[crouching].setOrigin(sprites[crouching].getLocalBounds().width / 2 - 8.f, sprites[crouching].getLocalBounds().height / 2 - 11.f);
    sprites[ascending].setOrigin(sprites[ascending].getLocalBounds().width / 2, sprites[ascending].getLocalBounds().height / 2);
    sprites[falling].setOrigin(sprites[falling].getLocalBounds().width / 2, sprites[falling].getLocalBounds().height / 2 + 3.f);


    state = normal;
    activeSprite = &sprites[normal];
}

// TODO: Find a way to control keypresses with polling in Game class and not assign activeSprite every update()
void Player::update(float deltatime) {
    if (Keyboard::isKeyPressed(Keyboard::S) && position.y < GROUND_HEIGHT) {
        switchState(crouching);
        acceleration.y = PUSH_DOWN_FORCE;
        //std::cout << "PUSHING DOWN!" << std::endl;
        return;
    }
    acceleration.y = 0.f;
    if (velocity.y > 0) {
        switchState(falling);
        return;
    } else if (velocity.y < 0) {
        switchState(ascending);
        return;
    }
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        //std::cout << "Crouch!" << std::endl;
        switchState(crouching);
        return;
    } else if (Keyboard::isKeyPressed(Keyboard::W)) {
        //std::cout << "Jump!" << std::endl;
        jump();
        return;
    }
    switchState(normal);
}

void Player::switchState(PlayerState state) {
    this->state = state;
    activeSprite = &sprites[state];
}

void Player::jump() {
    switchState(ascending);
    if (position.y >= GROUND_HEIGHT) {
        acceleration.y = 0.f;
        velocity.y = JUMP_VELOCITY;
    }
}
