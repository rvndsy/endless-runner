#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

class Background {
public:
    Background();
    void update();
    bool init();
    sf::Sprite sprite;
private:
    sf::Texture spriteTexture;
};
