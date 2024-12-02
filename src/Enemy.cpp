#include "../include/Enemy.hpp"

// Load a single sprite beyond the right of the screen and synchronise movement with the background
Enemy::Enemy(std::string spritePath, sf::Vector2f position, sf::Vector2f velocity) : Entity(sf::Vector2f(position.x+WINDOW_WIDTH+200.f, position.y), velocity) {
    if (!defaultTexture.loadFromFile(spritePath)) {
        throw std::runtime_error(std::string("Enemy::initSprite - defaultTexture.loadFromFile: Error loading sprite file \n") + spritePath);
    }
    defaultSprite.setTexture(defaultTexture);
    defaultSprite.setScale(SPRITE_SCALING, SPRITE_SCALING);
    // Set the origin of the sprite to middle of the sprite
    defaultSprite.setOrigin(defaultSprite.getLocalBounds().width / 2, defaultSprite.getLocalBounds().height / 2);
    position.y = position.y + defaultSprite.getLocalBounds().height / 2;
    activeSprite = &defaultSprite;
};
