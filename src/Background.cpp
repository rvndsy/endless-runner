#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <cmath>
#include <stdexcept>
#include "../include/Background.hpp"
#include "../include/Definitions.hpp"

// Creates ground and background sprites.
Background::Background() {
    if(!backgroundTexture.loadFromFile(BACKGROUND_SPRITE)) {
        throw std::runtime_error("Background - backgroundTexture.loadFromFile: Error loading background sprite file!\n");
    }
    if(!groundTexture.loadFromFile(GROUND_SPRITE)) {
        throw std::runtime_error("Background - groundTexture.loadFromFile: Error reading loading sprite file!\n");
    }
    sf::Vector2u size = backgroundTexture.getSize();
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setOrigin(0, 0);
    backgroundSprite.setScale(SPRITE_SCALING, SPRITE_SCALING);
    backgroundSprite.setColor(sf::Color(255, 255, 255, 255)); //set transparent at last value

    groundSprite.setTexture(groundTexture);
    groundSprite.setOrigin(0, -313);                        //ground sprite is set at the bottom
    groundSprite.setScale(SPRITE_SCALING, SPRITE_SCALING);
    groundSprite.setColor(sf::Color(255, 255, 255, 255));   //set transparent at last value
}
// Background and Ground is a png of the same image duplicated twice horizontally
void Background::update(float deltaTime, float velocity) {
    // Moving background sprite
    if (fabs(backgroundSprite.getPosition().x) >= backgroundSprite.getTexture()->getSize().x) { // image is scaled up 2x and we need to get half the width so we avoid adding `/ 2.f` at the end
        //std::cout << "Resetting background x position!" << std::endl;
        backgroundSprite.setPosition(0, 0);
    } else {
        backgroundSprite.move(velocity * deltaTime, 0);
    }

    // Moving ground sprite
    if (fabs(groundSprite.getPosition().x) >= groundSprite.getTexture()->getSize().x) { // image is scaled up 2x and we need to get half the width so we avoid adding `/ 2.f` at the end
        //std::cout << "Resetting ground x position!" << std::endl;
        groundSprite.setPosition(0, 0);
    } else {
        groundSprite.move(velocity * 1.5f * deltaTime, 0);
    }
}
