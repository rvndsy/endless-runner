#pragma once

#include <SFML/Graphics.hpp>
#include "Definitions.hpp"

using namespace sf;
// Player and children of Enemy inherit this class
// This class stores basic physics values, default sprites and textures, 
class Entity {
public:
    // The constructor sets position and velocity. Vertical position is set "on the ground".
    Entity(Vector2f position, Vector2f velocity) : position(position.x, position.y+GROUND_HEIGHT), velocity(velocity)  {}; // GROUND_HEIGHT effectively becomes y = 0

    // Destructors are unused right now
    virtual ~Entity() {};
    // Retrieve the current sprite to display
    virtual Sprite getSprite() {return *activeSprite;};
    // Update entity values and sprites while playing
    virtual void update(float deltaTime) = 0; // = 0 means the function is pure virtual
    // Enemies are synchronised with the background
    virtual void update(float deltaTime, float backgroundVelocity) = 0;

    // Update sprite positioning before displaying
    void updateEntityPos() {activeSprite->setPosition(position.x, position.y);};

    // Physics values getters, const is used to designate const-correctness
    Vector2f getPosition() const {return position;};
    Vector2f getVelocity() const {return velocity;};
    Vector2f getAcceleration() const {return acceleration;};
    // Physics values setters
    void setPosition(sf::Vector2f position) {this->position = position;};
    void setVelocity(sf::Vector2f velocity) {this->velocity = velocity;};
    void setAcceleration(sf::Vector2f acceleration) {this->acceleration = acceleration;};
protected:
    // Physics values to store position and movement in 2D
    Vector2f position = Vector2f(0.f, 0.f);
    Vector2f velocity = Vector2f(0.f, 0.f);      // 
    Vector2f acceleration = Vector2f(0.f, 0.f);  // Acceleration - rate of velocity change in px per sec
    // The sprite to be displayed currently
    Sprite * activeSprite;
};
