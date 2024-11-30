#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "../include/Entity.hpp"

enum PlayerState { normal, crouching, jumping };

class Player : public Entity {
public:
    Player(Vector2<int> position);
    void update();
    void updateActiveSprite();
    //bool initSprite();
    //void setState(PlayerState state) {this->state = state;};
    //PlayerState getState() {return state;};
private:
    PlayerState state;
    Texture crouchingTexture;
    Sprite crouchingSprite;
    Sprite jumpingSprite;
};
