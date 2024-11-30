#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

using namespace sf;
class Entity {
public:
    Entity(Vector2<int> position) : position(position) {};
    virtual ~Entity() {};
    Sprite getSprite() {return *activeSprite;};
    virtual void update(float deltaTime) = 0; // = 0 means the function is pure virtual

    virtual bool initSprite(std::string spritePath); // TODO: This is a mess...
protected:
    Texture defaultTexture;
    Sprite defaultSprite;
    Sprite * activeSprite;
    Vector2<int> position;
private:
};
