#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

// bg == background
class Background {
public:
    Background(float velocity);
    void update(float deltaTime, float velocity);
    //bool init();
    //float getGroundVelocity() { return groundVelocity; };
    sf::Sprite getBackgroundSprite() { return backgroundSprite; };
    sf::Sprite getGroundSprite() { return groundSprite; };
private:
  //float bgVelocity = BG_MOVE_RATE;
  //float groundVelocity = BG_MOVE_RATE;
  sf::Sprite backgroundSprite;
  sf::Sprite groundSprite;
  sf::Texture backgroundTexture;
  sf::Texture groundTexture;
};
