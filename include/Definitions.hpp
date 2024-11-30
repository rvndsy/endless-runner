#pragma once

#include <SFML/System/Vector2.hpp>

// constexpr is intended for values that are known and are evaluated at compile-time,

// Global values
constexpr int WINDOW_HEIGHT = 720;
constexpr int WINDOW_WIDTH = 1280;
constexpr int GROUND_HEIGHT = 200; //px from the bottom of screen

// Sprites
#define SPRITE_DIR_PATH "../sprites/"
#define BACKGROUND_SPRITE SPRITE_DIR_PATH "background.png"


// Player values
constexpr int PLAYER_START_X = 50;
constexpr int PLAYER_START_Y = WINDOW_HEIGHT-GROUND_HEIGHT;
constexpr int PLAYER_START_SCALE_X = 2;
constexpr int PLAYER_START_SCALE_Y = 2;
// Player sprites
#define PLAYER_SPRITE SPRITE_DIR_PATH "player.png"
#define PLAYER_CROUCHING_SPRITE SPRITE_DIR_PATH "player-crouching.png"

// Physics values - PIXELS PER SECOND
// Background
constexpr float BG_MOVE_RATE = -500.0f;
