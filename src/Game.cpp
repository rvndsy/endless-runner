#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cmath>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <random>
#include <string>
#include "../include/Game.hpp"
#include "../include/Background.hpp"
#include "../include/Player.hpp"
#include "../include/CrashedCar.hpp"
#include "../include/Bird.hpp"
#include "../include/Definitions.hpp"
#include "../include/Physics.hpp"

using namespace std;
Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Game", Style::Close) {
    cout << "Started game!" << endl;
    window.setFramerateLimit(240); // Limiting frame rate to some sane value
    if (!font.loadFromFile("../font/PublicPixel-rv0pA.ttf")) {
        throw runtime_error("Game::Game(): Failed to load font!");
    }
    titleText.setFont(font);
    titleText.setString(titleStr);
    titleText.setCharacterSize(64);
    titleText.setFillColor(sf::Color::White);
    titleText.setStyle(sf::Text::Bold);
    titleText.setPosition(WINDOW_WIDTH / 5.f * 2.f, WINDOW_HEIGHT / 2.f - 50.f);             // TODO: Move the sizing and moving around out of here...

    helpText.setFont(font);
    helpText.setString(helpStr);
    helpText.setCharacterSize(20);
    helpText.setFillColor(sf::Color::White);
    helpText.setStyle(sf::Text::Bold);
    helpText.setPosition(WINDOW_WIDTH / 5.f * 2.f, WINDOW_HEIGHT / 5.f * 3.f);

    scoreText.setFont(font);
    scoreText.setString("0");
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setStyle(sf::Text::Bold);

    state = menu;
}

void Game::run() {
    initialize();
    while (window.isOpen()) {
        pollGlobalEvents();
        if (state == playing) {
            update();
        }
        draw();
    }
}


void Game::initialize() {
    background = new Background(backgroundVelocity);
}

void Game::start() {
    state = playing;
    score = 0;
    scoreText.setString(to_string((int)score));
    scoreText.setPosition(WINDOW_WIDTH / 32.f * 29.f, WINDOW_HEIGHT / 64.f);
    backgroundVelocity = BG_START_VELOCITY;
    entities.push_back(new Player(Vector2(PLAYER_START_X, 0.f), Vector2(0.f, 0.f)));
    perSecondClock.restart();
}

// TODO: Replace with event listeners?
void Game::pollGlobalEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (state != playing && sf::Keyboard::isKeyPressed(Keyboard::Space)) {
                    cleanState();
                    start();
                }
                break;
            default: break;
        }
    }
}

void Game::update() {
    deltaTime = perFrameClock.restart().asSeconds();

    // Calculate background velocity and update background
    backgroundVelocity += deltaTime * BG_ACCELERATION_RATE;
    background->update(deltaTime, backgroundVelocity);

    // Spawn random enemy
    if (enemySpawnCountdown <= 0 && entities.size() < 5) {
        spawnRandomEnemy();
        enemySpawnCountdown = 1.f * (BG_START_VELOCITY / backgroundVelocity); //over time, spawn rates becomes faster
        //cout << enemySpawnCountdown << endl;
    } else {
        enemySpawnCountdown -= deltaTime;
    }

    // Update every entity
    for (size_t i = 0; i < entities.size(); i++) {
        entities[i]->update(deltaTime, backgroundVelocity*1.5f);
    }

    // Check for entities/enemies beyond the left side of screen and delete them
    for (size_t i = 1; i < entities.size(); i++) {
        if (entities[i]->position.x <= -100.f) {
            delete entities[i];
            entities.erase(entities.begin() + i);
        }
    }

    // for now only the player has gravity physics
    // and calculating Player physics before checking collision may cause a false-positive collision if the Player changes sprite above the Entity
    Physics::calculatePhysics(entities[0], deltaTime);
    for (size_t i = 1; i < entities.size(); i++) {
        if (Physics::collides(entities[0], entities[i])) {
            state = gameover;
        }
    }

    if (perSecondClock.getElapsedTime().asMilliseconds() >= 50) {
        perSecondClock.restart();
        score += backgroundVelocity/BG_START_VELOCITY*5-5;
        cout << floor(score) << endl;
    }
}

void Game::draw() {
    window.clear(sf::Color::Black);
    window.draw(background->getBackgroundSprite());
    window.draw(background->getGroundSprite());
    for (size_t i = 0; i < entities.size(); i++) {
        window.draw(entities[i]->getSprite());;
    }
    switch (state) {
        case gameover:
            drawGameOver();
            break;
        case menu:
            drawMainMenu();
            break;
        case playing:
            drawScore();
            break;
    }
    window.display();
}

void Game::drawMainMenu() {
    state = menu;
    titleText.setString(titleStr);
    window.draw(helpText);
    window.draw(titleText);
}

void Game::drawScore() {
    scoreText.setString(to_string((int)floor(score)));
    window.draw(scoreText);
}

void Game::drawGameOver() {
    scoreText.setString(to_string((int)floor(score)));
    titleText.setString(gameOverStr);
    window.draw(titleText);
    scoreText.setPosition(WINDOW_WIDTH / 5.f * 2.f, WINDOW_HEIGHT / 2.f + 100.f);
    string finalScoreStr = "Final score: ";
    finalScoreStr += to_string((int)floor(score));
    finalScoreStr += "\n\npress space to try again...";
    scoreText.setString(finalScoreStr);
    window.draw(scoreText);
}

void Game::spawnRandomEnemy() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> randomInt (1,5); // more values than used to randomize spawn rate

    int spawnerRoll = randomInt(gen);
    cout << "Rolled: " << spawnerRoll << endl;

    if (spawnerRoll == 1) {
        cout << " ...spawning crashed car" << endl;
        entities.push_back(new CrashedCar(backgroundVelocity));
    } else if (randomInt(gen) == 2) {

        uniform_real_distribution<float> randomHeight (-110.f, -210.f);

        float rolledBirdHeight = randomHeight(gen);
        cout << " ...spawning bird with height of " << rolledBirdHeight << endl;
        entities.push_back(new Bird(rolledBirdHeight, backgroundVelocity));
    }
}

void Game::cleanState() {
    for (size_t i = 0; i < entities.size(); ) {
        delete entities[i];
        entities.erase(entities.begin());
    }
}

Game::~Game() {
    delete background;
    for (size_t i = 0; i < entities.size(); ) {
        delete entities[i];
        entities.erase(entities.begin());
    }
    window.close();
}
