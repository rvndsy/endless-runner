#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

using namespace sf;
// Background class is responsible for updating the perpetually moving background.png and ground.png background/foreground sprites
class Background {
public:
    Background();
    ~Background() {}; // not used
    void update(float deltaTime, float velocity);                       // updates both sprite positions per update(), background velocity is stored in Game class
    Sprite getBackgroundSprite() { return backgroundSprite; };          // for drawing sprite in Game
    Sprite getGroundSprite() { return groundSprite; };                  // for drawing sprite in Game
private:
    // background.png, ground.png sprites are stored in one Background class
    Texture backgroundTexture;
    Texture groundTexture;
    Sprite backgroundSprite;
    Sprite groundSprite;
};
