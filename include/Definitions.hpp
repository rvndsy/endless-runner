#pragma once

// Not all global values are here. Some are in Entites.hpp or other header files.

// NOTE: constexpr is intended for values that are constant and are evaluated at compile-time

// Global window values
constexpr int WINDOW_HEIGHT = 720;
constexpr int WINDOW_WIDTH = 1280;
constexpr int GROUND_HEIGHT = WINDOW_HEIGHT-148; //px from the bottom of screen

// Global physics values
constexpr float GRAVITY_ACCEL = 10.f;        //px per sec^2
constexpr float GRAVITY_MULTIPLIER = 100.f;  //to make falling faster (more fun)

// Sprites
constexpr float SPRITE_SCALING = 2.f;        // All sprites are 2x bigger than (64x64 png is displayed as 128x128)
#define SPRITE_DIR_PATH "../sprites/"
#define BACKGROUND_SPRITE SPRITE_DIR_PATH "background.png"
#define GROUND_SPRITE SPRITE_DIR_PATH "ground.png"

// PHYSICS VALUES - PIXELS PER SECOND
// Background
constexpr float BG_START_VELOCITY = -500.0f;
constexpr float BG_ACCELERATION_RATE = -5.0f;
