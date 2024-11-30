#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "../include/Game.hpp"
#include "../include/Background.hpp"
#include "../include/Player.hpp"
#include "../include/Definitions.hpp"
#include "../include/Physics.hpp"

Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game", Style::Close) {
    std::cout << "Started game!" << std::endl;
    window.setFramerateLimit(240); // Limiting frame rate to some sane value
}

void Game::run() {
    initialize();
    while (window.isOpen())
    {
        deltaTime = constantClock.restart().asSeconds();
        pollGlobalEvents();
        update();
        draw();
    }
}

void Game::initialize() {
    if (!background.init()) {
        std::cout << "Failed to initialize background!" << std::endl;
        return;
    }
    Player * player = new Player(Vector2(PLAYER_START_X, 0.f), Vector2(0.f, 0.f));
    if (player == nullptr) {
        std::cout << "Failed to initialize player!" << std::endl;
        return;
    }
    entities.push_back(player);
}

// TODO: Replace with event listeners?
void Game::pollGlobalEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
        }
    }
}

// TODO: Add some sort of entity list
//       Add a constant clock rate
void Game::update() {
    background.update(deltaTime);
    for (auto &entity : entities) {
        entity->update(deltaTime);
    }
    for (auto &entity : entities) {
        Physics::calculatePhysics(entity, deltaTime);
    }
}

void Game::draw() {
    window.clear(sf::Color::Black);
    window.draw(background.bgSprite);
    window.draw(background.groundSprite);
    for (auto &entity : entities) {
        window.draw(entity->getSprite());
    }
    window.display();
}

Game::~Game() {
    for (auto &entity : entities) {
        delete entity;
    }
    window.close();
}
