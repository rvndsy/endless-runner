#include <SFML/System/Vector2.hpp>
#include <iostream>
#include "../include/Entity.hpp"

using namespace sf;
bool Entity::initSprite(std::string path) {
    if(!defaultTexture.loadFromFile(path)) {
        std::cout << "Entity::initSprite: Failed to load texture - " << path << std::endl;
        return false;
    }
    defaultSprite.setTexture(defaultTexture);
    activeSprite = &defaultSprite;
    return true;
}
