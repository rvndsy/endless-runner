#include "../include/CrashedCar.hpp"

// Update horizontal position synchronised with the background
void CrashedCar::update(float deltaTime, float backgroundVelocity) {
    position.x += deltaTime * backgroundVelocity;
    updateEntityPos();
}
