#include "../include/Background.hpp"
#include "../include/Definitions.hpp"
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <cmath>
#include <iostream>

Background::Background() {
    if(!spriteTexture.loadFromFile(BACKGROUND_SPRITE)) {
        std::cout << "Error reading background file!" << std::endl;
    }
    sprite = sf::Sprite();
    Background::init();
}

bool Background::init() {
    sf::Vector2u size = spriteTexture.getSize();
    sprite.setTexture(spriteTexture);
    sprite.setOrigin(0, 0);
    sprite.setColor(sf::Color(255, 255, 255, 128));
    return 1;
}
// Background is a png of the same image duplicated twice horizontally
void Background::update() {
    if (fabs(sprite.getPosition().x) >= sprite.getTexture()->getSize().x / 2.f) {
        //std::cout << "Resetting background x position!" << std::endl;
        sprite.setPosition(0, 0);
    } else {
        sprite.move(-5.f, 0);
        sf::sleep(sf::milliseconds(10));
        //std::cout << sprite.getTexture()->getSize().x << std::endl;
    }
}
