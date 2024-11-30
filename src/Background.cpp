#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <cmath>
#include <iostream>
#include "../include/Background.hpp"
#include "../include/Definitions.hpp"

bool Background::init() {
    if(!bgTexture.loadFromFile(BACKGROUND_SPRITE)) {
        std::cout << "Error reading background file!" << std::endl;
        return 0;
    }
    if(!groundTexture.loadFromFile(GROUND_SPRITE)) {
        std::cout << "Error reading background file!" << std::endl;
        return 0;
    }
    sf::Vector2u size = bgTexture.getSize();
    bgSprite.setTexture(bgTexture);
    bgSprite.setOrigin(0, 0);
    bgSprite.setScale(SPRITE_SCALING, SPRITE_SCALING);
    bgSprite.setColor(sf::Color(255, 255, 255, 255)); //set transparent at last value

    groundSprite.setTexture(groundTexture);
    groundSprite.setOrigin(0, -313);
    groundSprite.setScale(SPRITE_SCALING, SPRITE_SCALING);
    groundSprite.setColor(sf::Color(255, 255, 255, 255)); //set transparent at last value
    return 1;
}
// Background and Ground is a png of the same image duplicated twice horizontally
void Background::update(float deltaTime) {
    // Moving background sprite
    if (fabs(bgSprite.getPosition().x) >= bgSprite.getTexture()->getSize().x) { // image is scaled up 2x and we need to get half the width so we avoid adding `/ 2.f` at the end
        std::cout << "Resetting background x position!" << std::endl;
        bgSprite.setPosition(0, 0);
    } else {
        bgSprite.move(bgVelocity * -deltaTime, 0);
        bgVelocity += deltaTime * BG_ACCELERATION_RATE;
    }

    // Moving ground sprite
    if (fabs(groundSprite.getPosition().x) >= groundSprite.getTexture()->getSize().x) { // image is scaled up 2x and we need to get half the width so we avoid adding `/ 2.f` at the end
        std::cout << "Resetting ground x position!" << std::endl;
        groundSprite.setPosition(0, 0);
    } else {
        groundSprite.move(groundVelocity * 1.5f * -deltaTime, 0);
        groundVelocity += deltaTime * BG_ACCELERATION_RATE;
    }
}
