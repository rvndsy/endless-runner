#include "../include/Wall.hpp"

// Update horizontal position synchronised with the background
void Wall::update(float deltaTime, float backgroundVelocity) {
    position.x += deltaTime * backgroundVelocity;
    updateEntityPos();
}
