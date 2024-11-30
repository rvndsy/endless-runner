#pragma once

#include "Definitions.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

// bg == background
class Background {
public:
    void update(float deltaTime);
    bool init();
    sf::Sprite bgSprite;
    sf::Sprite groundSprite;
private:
    float bgVelocity = BG_MOVE_RATE;
    float groundVelocity = BG_MOVE_RATE;
    sf::Texture bgTexture;
    sf::Texture groundTexture;
};
