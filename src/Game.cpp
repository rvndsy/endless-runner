#include <SFML/Graphics.hpp>            // This includes basically everything to do with SFML
#include <iostream>
#include <random>
#include "../include/Definitions.hpp"
#include "../include/Physics.hpp"
#include "../include/Game.hpp"
#include "../include/Background.hpp"
#include "../include/Player.hpp"
#include "../include/CrashedCar.hpp"
#include "../include/Bird.hpp"
#include "../include/Wall.hpp"

using namespace std;
Game::Game() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Endless Runner", Style::Close) {
    window.setFramerateLimit(240); // Limiting frame rate to some sane value
    if (!font.loadFromFile("../font/PublicPixel-rv0pA.ttf")) {  // public domain font  >>  https://www.fontspace.com/public-pixel-font-f72305
        throw runtime_error("Game::Game(): Failed to load font!");
    }
    // Used to display all the very large texts
    titleText.setFont(font);
    titleText.setString(titleStr);
    titleText.setCharacterSize(64);
    titleText.setFillColor(sf::Color::White);
    titleText.setStyle(sf::Text::Bold);

    // Shows information about how to play
    helpText.setFont(font);
    helpText.setString(helpStr);
    helpText.setCharacterSize(20);
    helpText.setFillColor(sf::Color::White);
    helpText.setStyle(sf::Text::Bold);

    // Shows the score while playing and after gameover
    scoreText.setFont(font);
    scoreText.setString("0");
    scoreText.setCharacterSize(20);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setStyle(sf::Text::Bold);

    // For feedback when game is paused
    pauseText.setFont(font);
    pauseText.setString(pausedStr);
    pauseText.setCharacterSize(28);
    pauseText.setFillColor(sf::Color::White);
    pauseText.setStyle(sf::Text::Bold);

    // Game starts in the menu
    setState(menu);
    cout << "Started game!" << endl;
}
// The main game loop to run in main()
void Game::run() {
    initialize();
    while (window.isOpen()) {
        pollGlobalEvents();
        if (state == playing || state == paused) {
            update();
        }
        draw();
    }
}
// For setting up the game at start-up
void Game::initialize() {
    clearState();
    background = new Background();
}
// Starting the game!
void Game::start() {
    // Creating Player Entity. It is always the 0-th in the Entity list.
    player = new Player(Vector2(PLAYER_START_X, 0.f), Vector2(0.f, 0.f));
    entities.push_back(player); 
    constIntervalClock.restart();
    setState(playing);
}
// Listen for global Key/Mouse events
void Game::pollGlobalEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();         // this also calls the destructor
                break;
            case sf::Event::KeyPressed:
                if ((state == gameover || state == menu) && sf::Keyboard::isKeyPressed(Keyboard::Space)) {
                    clearState();       // before restarting the game reset all values
                    start();
                } else if (state == playing && sf::Keyboard::isKeyPressed(Keyboard::Escape)) {
                    drawPausedText();
                    setState(paused);
                    sf::sleep(sf::milliseconds(100));
                } else if (state == paused && sf::Keyboard::isKeyPressed(Keyboard::Escape)) {
                    state = playing;
                }
                break;
            default: break;
        }
    }
}
// Update Entity and Game values, Sprite positions and physics
void Game::update() {
    // If paused keep the clock at 0
    if (state == paused) {
        perFrameClock.restart();
        return;
    }
    // Calculating time it took between frames for accurate movement and physics calculations
    deltaTime = perFrameClock.restart().asSeconds();

    // Calculate background velocity and update background
    backgroundVelocity += deltaTime * BG_ACCELERATION_RATE;
    background->update(deltaTime, backgroundVelocity);

    // Spawn random enemy when countdown hits 0
    if (enemySpawnCountdown <= 0 && entities.size() < 5) {
        spawnRandomEnemy();
        enemySpawnCountdown = 0.8f * (BG_START_VELOCITY / backgroundVelocity); //over time, spawn rates becomes faster
    } else {
        enemySpawnCountdown -= deltaTime;
    }

    // Update every entity including their positions
    for (size_t i = 0; i < entities.size(); i++) {
        entities[i]->update(deltaTime, backgroundVelocity*1.5f);
    }

    // Check for entities/enemies beyond the left side of screen and delete them
    for (size_t i = 1; i < entities.size(); i++) {
        if (entities[i]->getPosition().x <= -100.f) {
            entities.erase(entities.begin() + i);
        }
    }

    // for now only the player has gravity physics
    // and calculating Player physics before checking collision prevents a false-positive collision if the Player changes sprite above the Entity
    Physics::calculatePhysics(entities[0], deltaTime);
    for (size_t i = 1; i < entities.size(); i++) {
        if (Physics::collides(entities[0], entities[i])) {
            setState(gameover);     // If Player hits something it is game over
        }
    }

    // Increment the score every 50 milliseconds. The faster the backgroundVelocity the greater the increment.
    if (constIntervalClock.getElapsedTime().asMilliseconds() >= 50) {
        constIntervalClock.restart();
        score += backgroundVelocity/BG_START_VELOCITY*5-5;  //*5-5 makes backgroundVelocity/BG_START_VELOCITY more significant in increment
    }
}
// Drawing Drawable's according to the current state and whether entities exist on the window
void Game::draw() {
    window.clear(sf::Color::Black);

    // Drawing background
    window.draw(background->getBackgroundSprite());
    window.draw(background->getGroundSprite());

    // Drawing entities
    for (size_t i = 0; i < entities.size(); i++) {
        window.draw(entities[i]->getSprite());
    }

    // Drawing Text/UI
    switch (state) {
        case gameover:
            drawGameOverText();
            break;
        case menu:
            drawMainMenuText();
            break;
        case playing:
            drawScoreText();
            break;
        case paused:
            drawScoreText();
            drawPausedText();
            break;
        default: break;
    }

    window.display();
}
// Switch to a different game state and set-up misc things like text
void Game::setState(GameState stateTo) {
    state = stateTo;
    switch (state) {
        case gameover:
            prepareGameOverText();
            break;
        case menu:
            prepareMainMenuText();
            break;
        case paused:
            preparePausedText();
            break;
        case playing:
            preparePlayingText();
            break;
        default: break;
    }
}
// 
// Below are functions for configuring Text/UI when switching states, loading text happens in constructor
//
void Game::preparePlayingText() {
    scoreText.setString(to_string((int)score));
    scoreText.setPosition(WINDOW_WIDTH / 32.f * 29.f, WINDOW_HEIGHT / 64.f);
}
void Game::prepareMainMenuText() {
    helpText.setPosition(WINDOW_WIDTH / 32.f * 15.f, WINDOW_HEIGHT / 32.f * 15.f);
    titleText.setPosition(WINDOW_WIDTH / 32.f, WINDOW_HEIGHT / 16.f * 9.f);
    titleText.setString(titleStr);
}
void Game::prepareGameOverText() {
    scoreText.setString(to_string((int)floor(score)));
    titleText.setPosition(WINDOW_WIDTH / 5.f * 2.f, WINDOW_HEIGHT / 2.f - 50.f);
    titleText.setString(gameOverStr);
    scoreText.setPosition(WINDOW_WIDTH / 5.f * 2.f, WINDOW_HEIGHT / 2.f + 100.f);
    string finalScoreStr = "Final score: ";
    finalScoreStr += to_string((int)floor(score));
    finalScoreStr += "\n\npress space to try again...";
    scoreText.setString(finalScoreStr);
}
void Game::preparePausedText() {
    pauseText.setPosition(WINDOW_WIDTH / 5.f, WINDOW_HEIGHT / 5.f * 4.f);
}
//
// Below are functions for drawing the Text/UI of some state
//
void Game::drawMainMenuText() {
    window.draw(titleText);
    window.draw(helpText);
}
void Game::drawScoreText() {
    scoreText.setString(to_string((int)floor(score)));
    window.draw(scoreText);
}
void Game::drawGameOverText() {
    window.draw(titleText);
    window.draw(scoreText);
}
void Game::drawPausedText() {
    window.draw(pauseText);
}
// Attempts to spawn a random Enemy every time enemySpawnCountdown hits 0, doesn't have 100% success rate on purpose
void Game::spawnRandomEnemy() {
    // Setting up random device
    mt19937 gen(rd());
    uniform_int_distribution<int> randomInt (1,6); // more values than used to randomize spawn rate

    if (randomInt(gen) == 1) {
        cout << " ...spawning crashed car" << endl;
        entities.push_back(new CrashedCar(backgroundVelocity));     // new Enemies need the current backgroundVelocity to synchronise with the movement of background
    } else if (randomInt(gen) == 2) {
        uniform_real_distribution<float> randomHeight (-60.f, -220.f);     // a new Bird is given a random height
        float rolledBirdHeight = randomHeight(gen);

        cout << " ...spawning bird with height of " << rolledBirdHeight << endl;
        entities.push_back(new Bird(backgroundVelocity, rolledBirdHeight));
    } else if (randomInt(gen) == 3) {
        cout << " ...spawning crashed car" << endl;
        entities.push_back(new Wall(backgroundVelocity));     // new Enemies need the current backgroundVelocity to synchronise with the movement of background
    }
}
// For clearing variables because sometimes values/objects persist in memory after closing...
void Game::clearState() {
    backgroundVelocity = BG_START_VELOCITY;
    perFrameClock.restart();
    score = 0;
    deltaTime = 0;
    enemySpawnCountdown = 0.8f;
    for (size_t i = 0; i < entities.size(); i++) {
        delete entities[i];    // deletes enemies and the player
    }
    entities.clear();
}
// Destructor deletes background in addition to clearState() as the background otherwise should persist in all states.
Game::~Game() {
    delete background;
    clearState();
    window.close();
}
