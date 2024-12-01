#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Window.hpp>
#include <random>
#include <vector>
#include "Background.hpp"
#include "Entity.hpp"

enum GameState { menu, playing, gameover };

class Game {
public:
    Game();
    ~Game();
    void run();                     // Entry point in Main
    float getBackgroundVelocity() {return backgroundVelocity;};     // WARN: I dont think this is used....
private:
    GameState state;
    sf::Clock perFrameClock;        // For deltaTime
    sf::Clock perSecondClock;       // For deltaTime
    sf::Time elapsedTime;           // For score
    sf::RenderWindow window;        // The main window
    sf::Font font;
    std::string titleStr = "Welcome!";
    std::string helpStr = "Objective: don't hit anything!\n\nControls:\n\nW - to jump\n\nS - to crouch or fall faster\n\npress space to start...";
    std::string gameOverStr = "Game Over!";
    sf::Text titleText;
    sf::Text helpText;
    sf::Text scoreText;
    std::vector<Entity*> entities;  // Entity 0 is always the Player, the rest are Enemies
    Background * background;        // Made up of the ground and background. Not an Entity.
    float backgroundVelocity;       // Speed of background and ground elements. Affects Entity speed and decreases enemySpawnCountDown rate over time.
    float deltaTime;                // For maintaining physics consistency across variable framerate
    float enemySpawnCountdown;      // Time between Enemy spawning attempts. Decreased over time by by backgroundVelocity.
    double score = 0;
    bool isGameOver = false;                // If true - the player is "dead" and gameOver() is executed
    void initialize();
    void start();
    void pollGlobalEvents();        // Global Keyboard and Mouse inputs
    void update();                  // Attempts Enemy spawn, updates each Entity, updates physics
    void draw();                    // Draws all Sprites
    void spawnRandomEnemy();        // Attempts to spawn a random Enemy during update() every enemySpawnCountdown seconds. A spawn is not supposed to be guaranteed.
    void drawGameOver();                // Show game over screen.
    void drawScore();
    void drawMainMenu();
    void cleanState();
};
