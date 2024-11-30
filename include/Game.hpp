#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
#include <vector>
#include "Background.hpp"
#include "Entity.hpp"

class Game {
public:
    Game();
    ~Game();
    void run();
private:
    std::vector<Entity*> entities;
    sf::Clock clock;
    sf::RenderWindow window;
    Background background;
    void initialize();
    void pollGlobalEvents();
    void update();
    void draw();
    void kill();
};
