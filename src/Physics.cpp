#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include "../include/Physics.hpp"

// y axis is flipped because of SFML window
void Physics::calculatePhysics(Entity *& entity, float deltaTime) {
    // Get values
    Vector2f velocity = entity->getVelocity();
    Vector2f position = entity->getPosition();

    // Update vertical velocity and position if the Entity is above the ground or is moving vertically
    if (velocity.y < 0 || position.y < GROUND_HEIGHT) {
        velocity.y += deltaTime * (GRAVITY_ACCEL + entity->getAcceleration().y) * GRAVITY_MULTIPLIER;
        position.y += deltaTime * velocity.y;
    }

    // Don't update position and velocity if the player is on the ground
    if (position.y >= GROUND_HEIGHT) {
        position.y = GROUND_HEIGHT;
        velocity.y = 0;
    }

    // Set values
    entity->setPosition(position);
    entity->setVelocity(velocity);
    entity->updateEntityPos();
}

// Check if two sprites collide - uses SFML provided function
bool Physics::collides(Entity * a, Entity * b) {
    return a->getSprite().getGlobalBounds().intersects(b->getSprite().getGlobalBounds());
}
