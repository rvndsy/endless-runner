#pragma once

#include "Entity.hpp"

class Physics {
public:
    static void calculatePhysics(Entity *& entity, float deltaTime);
    static bool collides(Entity *, Entity *);
};
