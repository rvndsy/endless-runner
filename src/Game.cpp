#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "../include/Game.hpp"
#include "../include/Background.hpp"
#include "../include/Player.hpp"
#include "../include/Definitions.hpp"

Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!") {
    std::cout << "Started game!" << std::endl;
}

void Game::run() {
    initialize();
    while (window.isOpen())
    {
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
    Player * player = new Player(Vector2(0, 0));
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
    background.update();
    for (auto &entity : entities) {
        entity->update();
    }
}

void Game::draw() {
    window.clear(sf::Color::Black);
    window.draw(background.sprite);
    for (auto &entity : entities) {
        window.draw(entity->getSprite());
    }
    window.display();
}

void Game::kill() {
    for (auto &entity : entities) {
        delete entity;
    }
    window.close();
}

Game::~Game() {
    kill();
}
