#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "../include/Definitions.hpp"
#include "../include/Player.hpp"

Player::Player(sf::Vector2<int> position) : Entity(position) {
    Entity::initSprite(PLAYER_SPRITE);
    defaultSprite.setPosition(PLAYER_START_X, PLAYER_START_Y);
    defaultSprite.setScale(PLAYER_START_SCALE_X, PLAYER_START_SCALE_Y);

    crouchingTexture.loadFromFile(PLAYER_CROUCHING_SPRITE);
    crouchingSprite.setTexture(crouchingTexture);
    crouchingSprite.setPosition(PLAYER_START_X, PLAYER_START_Y);
    crouchingSprite.setScale(PLAYER_START_SCALE_X, PLAYER_START_SCALE_Y);

    state = normal;
}

// TODO: Find a different way to not updateActiveSprite() every update()
void Player::update() {
    if (Keyboard::isKeyPressed(Keyboard::S)) {
        std::cout << "Crouch!" << std::endl;
        state = crouching;
        activeSprite = &crouchingSprite;
    } else if (Keyboard::isKeyPressed(Keyboard::W)) {
        std::cout << "Jump!" << std::endl;
        state = jumping;
        //activeSprite = &jumpingSprite;
    } else {
        std::cout << "Return to normal" << std::endl;
        state = normal;
        activeSprite = &defaultSprite;
    }
}

//void Player::updateActiveSprite() {
//    std::cout << "Updating active sprite for player" << std::endl;
//    switch (state) {
//        case crouching:
//            activeSprite = &crouchingSprite;
//            break;
////      case jumping:
////          activeSprite = &crouchingSprite;
////          break;
//        case normal:
//            activeSprite = &sprite;
//            break;
//    }
//}
