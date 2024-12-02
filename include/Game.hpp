#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include "Background.hpp"
#include "Entity.hpp"
#include "Player.hpp"

// Datatype for storing the current type of game state
enum GameState { menu, paused, playing, gameover };

class Game {
public:
    Game();
    ~Game();
    void run();                     // Entry point in Main
private:
    sf::RenderWindow window;        // The main window that every Drawable is drawn onto
    sf::Clock perFrameClock;        // For keeping deltaTime
    sf::Clock constIntervalClock;   // For updating score
    std::random_device rd;          // For spawning enemies

    std::vector<Entity*> entities;  // Entity 0 is always the Player, the rest are Enemies
    Background * background;        // Made up of the ground and background. Not an Entity.
    Player * player;

    GameState state;
    float backgroundVelocity = 0;   // Speed of background and ground elements. Affects Entity speed and decreases enemySpawnCountDown rate over time.
    float deltaTime = 0;            // For maintaining physics consistency across variable framerate
    float enemySpawnCountdown = .8f;// Time between Enemy spawning attempts. Decreased over time by by backgroundVelocity.
    double score = 0;
 
    // Main game loop functions
    void initialize();              // Runs at the very beginning of game loop. Clears state and creates background.
    void pollGlobalEvents();        // Handle global Keyboard and Mouse inputs. Player input handling is in Player::update()
    void update();                  // Attempts Enemy spawn, updates each Entity and Player, updates physics
    void draw();                    // Draws all Sprites depending on state

    // For switching states
    void start();                   // Start the game!
    void setState(GameState state); // Switch game state and set up the appropriate Text/UI or other things
    void clearState();              // Reset all important Game values and delete all Entities

    // Miscellaneous
    void spawnRandomEnemy();        // Attempts to spawn a random Enemy during update() every enemySpawnCountdown seconds. A spawn is not supposed to be guaranteed.

    // Text/UI values
    std::string titleStr = "Welcome!";
    std::string helpStr = "Objective: don't hit anything!\n\nControls:\n\nW - to jump\n\nS - to crouch or fall faster\n\nESC - pause, unpause\n\npress space to start...";
    std::string gameOverStr = "Game Over!";
    std::string pausedStr = "|| pause\t...press ESC to resume";
    // Text/UI objects
    sf::Font font;
    sf::Text titleText;
    sf::Text helpText;
    sf::Text scoreText;
    sf::Text pauseText;
    // Text/UI functions to position Text and set the string
    void prepareGameOverText();
    void prepareMainMenuText();
    void preparePausedText();
    void preparePlayingText();
    // Text/UI functions to draw Text
    void drawGameOverText();
    void drawScoreText();
    void drawMainMenuText();
    void drawPausedText();
};
