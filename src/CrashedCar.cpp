#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>
#include "../include/Definitions.hpp"
#include "../include/CrashedCar.hpp"

CrashedCar::CrashedCar(float backgroundVelocity) : Enemy(sf::Vector2<float>(WINDOW_WIDTH, 0), sf::Vector2<float>(backgroundVelocity, 0)) {
    if (!defaultTexture.loadFromFile(CRASHED_CAR_SPRITE)) {
        throw std::runtime_error("CrashedCar - defaultTexture.loadFromFile: Error loading sprite file!\n");
    }
    defaultSprite.setTexture(defaultTexture);
    defaultSprite.setScale(SPRITE_SCALING, SPRITE_SCALING);
    defaultSprite.setOrigin(defaultSprite.getLocalBounds().width / 2, defaultSprite.getLocalBounds().height / 2);
    position.y = position.y + defaultSprite.getLocalBounds().height / 2;
    activeSprite = &defaultSprite;
}

void CrashedCar::update(float deltaTime, float backgroundVelocity) {
    position.x += deltaTime * backgroundVelocity;
    //std::cout << velocity.x << " - " << position.x << std::endl;
    updateEntityPos();
}
