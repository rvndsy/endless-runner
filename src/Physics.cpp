#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include "../include/Physics.hpp"

// y axis is flipped because of SFML window
void Physics::calculatePhysics(Entity *& entity, float deltaTime) {
    //std::cout << entity->position.y << " - " << entity->velocity.y << std::endl;
    if (entity->velocity.y < 0 || entity->position.y < GROUND_HEIGHT) {
        entity->velocity.y += deltaTime * (GRAVITY_ACCEL + entity->acceleration.y) * GRAVITY_MULTIPLIER;
        entity->position.y += deltaTime * entity->velocity.y;
        //std::cout << "Physics: Jumping..." << std::endl;
    }
    if (entity->position.y >= GROUND_HEIGHT) {
        entity->position.y = GROUND_HEIGHT;
        entity->velocity.y = 0;
        //std::cout << "Physics: On ground..." << std::endl;
    }

    entity->updateEntityPos();
}

bool Physics::collides(Entity * a, Entity * b) {
    return a->getSprite().getGlobalBounds().intersects(b->getSprite().getGlobalBounds());
}
