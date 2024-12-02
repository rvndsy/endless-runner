#pragma once

#include "Entity.hpp"

// Class to handle gravity physics and collisions between entities.
class Physics {
public:
    // Calculate Physics - currently only gravity for the Player
    static void calculatePhysics(Entity *& entity, float deltaTime);
    // Check if two sprites collide - uses SFML intersects()
    static bool collides(Entity *, Entity *);
};
