#include "../include/Bird.hpp"

// Update horizontal position synchronised with the background
void Bird::update(float deltaTime, float backgroundVelocity) {
    position.x += deltaTime * backgroundVelocity * 1.2f;  // Bird moves slightly faster
    updateEntityPos();
}
