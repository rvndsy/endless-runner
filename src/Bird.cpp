#include <stdexcept>
#include "../include/Bird.hpp"

Bird::Bird(float height, float backgroundVelocity) : Enemy(sf::Vector2<float>(WINDOW_WIDTH, height), sf::Vector2<float>(backgroundVelocity+10, 0)) {
    if (!defaultTexture.loadFromFile(BIRD_SPRITE)) {
        throw std::runtime_error("Bird - defaultTexture.loadFromFile: Error loading sprite file!\n");
    }
    defaultSprite.setTexture(defaultTexture);
    defaultSprite.setScale(SPRITE_SCALING, SPRITE_SCALING);
    defaultSprite.setOrigin(defaultSprite.getLocalBounds().width / 2, defaultSprite.getLocalBounds().height / 2);
    position.y = position.y + defaultSprite.getLocalBounds().height / 2;
    activeSprite = &defaultSprite;
}

void Bird::update(float deltaTime, float backgroundVelocity) {
    position.x += deltaTime * backgroundVelocity * 1.2f;  // Bird moves slightly faster
    //std::cout << velocity.x << " - " << position.x << std::endl;
    updateEntityPos();
}
