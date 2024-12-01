#pragma once

#include "Definitions.hpp"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

using namespace sf;
class Entity {
public:
    Entity(Vector2<float> position, Vector2<float> velocity) : position(position.x, position.y+GROUND_HEIGHT), velocity(velocity) {}; // GROUND_HEIGHT effectively becomes y = 0
    virtual ~Entity() {};
    virtual Sprite getSprite() {return *activeSprite;};
    void updateEntityPos() {activeSprite->setPosition(position.x, position.y);};
    virtual void update(float deltaTime) = 0; // = 0 means the function is pure virtual
    virtual void update(float deltaTime, float backgroundVelocity) = 0;

    // Getters
    //sf::Vector2<float> getPosition() {return position;};
    //sf::Vector2<float> getVelocity() {return velocity;};
    //sf::Vector2<float> getAcceleration() {return acceleration;};
    //float getVelocityY() {return velocity.y;};
    //float getPositionY() {return position.y;};
    //float getVelocityX() {return velocity.x;};
    //float getPositionX() {return position.x;};
    // Setters
    //void setPosition(sf::Vector2<float> position) {this->position = position;};
    //void setVelocity(sf::Vector2<float> velocity) {this->velocity = velocity;};
    //void setAcceleration(sf::Vector2<float> acceleration) {this->acceleration = acceleration;};
    //void setVelocityY(float velocityY) {velocity.y = velocityY;};
    //void setPositionY(float positionY) {position.y = positionY;};
    //void setVelocityX(float velocityX) {velocity.x = velocityX;};
    //void setPositionX(float positionX) {position.x = positionX;};
    Vector2<float> position; // NOTE: Moved from private to public!
    Vector2<float> velocity = Vector2(0.f, 0.f);
    Vector2<float> acceleration = Vector2(0.f, 0.f); // Acceleration - rate of velocity change in px per sec  NOTE: Not sure if i need this!
protected:
    Texture defaultTexture;
    Sprite defaultSprite;
    Sprite * activeSprite;
};
