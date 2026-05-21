#ifndef GAME_PARAMS_H
#define GAME_PARAMS_H

// --- Screen Parameters ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// --- Game Logic Parameters ---
const int INITIAL_LIVES = 3;

// --- Paddle Parameters ---
const float PADDLE_WIDTH = 24.0f;
const float PADDLE_HEIGHT = 4.0f;
const float PADDLE_SPEED = 90.0f; // pixels per second

// --- Ball Parameters ---
const float BALL_RADIUS = 2.0f;
const float BALL_SPEED_BASE = 35.0f; // pixels per second

// --- Block Parameters ---
const int BLOCK_ROWS = 4;
const int BLOCK_COLS = 8;
const float BLOCK_WIDTH = (float)SCREEN_WIDTH / BLOCK_COLS;
const float BLOCK_HEIGHT = 6.0f;
const float BLOCK_START_Y = 12.0f;

#endif // GAME_PARAMS_H
