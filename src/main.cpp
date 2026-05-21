#include <Arduino.h>
#include "config.h"
#include "game_params.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// --- Enums & Structs ---
enum GameState {
    STATE_START_SCREEN,
    STATE_SERVE_WAIT,
    STATE_PLAYING,
    STATE_GAME_OVER,
    STATE_WIN
};

struct Paddle {
    float x;
    float y;
    float width;
    float height;
    float speed;
};

struct Ball {
    float x;
    float y;
    float radius;
    float velocity_x;
    float velocity_y;
};

// --- Global Variables ---
GameState currentState = STATE_START_SCREEN;

Paddle paddle;
Ball ball;

bool blocks[BLOCK_ROWS][BLOCK_COLS];

int lives = INITIAL_LIVES;
unsigned long stateStartTime = 0;
unsigned long lastFrameTime = 0;
unsigned long blueLedTurnOffTime = 0;
unsigned long redLedTurnOffTime = 0;

// --- Function Prototypes ---
void initGame();
void resetLevel();
void updatePaddle(float dt);
void updateBall(float dt);
void drawStartScreen();
void drawPlayingScreen();
void drawGameOverScreen();
void drawWinScreen();

void setup() {
    Serial.begin(115200);

    // Initialize LEDs
    pinMode(PIN_LED_RED, OUTPUT);
    pinMode(PIN_LED_BLUE, OUTPUT);
    digitalWrite(PIN_LED_RED, LOW);
    digitalWrite(PIN_LED_BLUE, LOW);

    // Initialize Buttons
    pinMode(PIN_BUTTON_1_LEFT, INPUT_PULLUP);
    pinMode(PIN_BUTTON_2_CENTER, INPUT_PULLUP);

    // Initialize OLED
    Wire.begin(PIN_OLED_SDA, PIN_OLED_SCL);
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
    }
    Wire.setClock(400000); // 400kHz I2C for faster rendering
    display.setRotation(2); // Match breadboard

    initGame();
    stateStartTime = millis();
    lastFrameTime = millis();
}

void loop() {
    unsigned long currentMillis = millis();
    float dt = (currentMillis - lastFrameTime) / 1000.0f;
    lastFrameTime = currentMillis;

    // Handle asynchronous LEDs
    if (blueLedTurnOffTime > 0 && currentMillis > blueLedTurnOffTime) {
        digitalWrite(PIN_LED_BLUE, LOW);
        blueLedTurnOffTime = 0;
    }
    
    if (redLedTurnOffTime > 0 && currentMillis > redLedTurnOffTime && currentState != STATE_GAME_OVER) {
        digitalWrite(PIN_LED_RED, LOW);
        redLedTurnOffTime = 0;
    }

    // Input state
    bool leftPressed = (digitalRead(PIN_BUTTON_1_LEFT) == LOW);
    bool rightPressed = (digitalRead(PIN_BUTTON_2_CENTER) == LOW);

    display.clearDisplay();

    switch(currentState) {
        case STATE_START_SCREEN:
            drawStartScreen();
            if (currentMillis - stateStartTime > 3000 || leftPressed || rightPressed) {
                initGame();
                currentState = STATE_SERVE_WAIT;
                stateStartTime = currentMillis;
            }
            break;

        case STATE_SERVE_WAIT:
            updatePaddle(dt);
            // Ball rests on paddle
            ball.x = paddle.x + paddle.width / 2.0f;
            ball.y = paddle.y - ball.radius - 1.0f;
            
            drawPlayingScreen();
            
            if (currentMillis - stateStartTime > 2000) {
                // Auto serve upwards, slightly angled
                ball.velocity_x = (random(0, 2) == 0 ? -1.0f : 1.0f) * BALL_SPEED_BASE * 0.7f;
                ball.velocity_y = -BALL_SPEED_BASE;
                currentState = STATE_PLAYING;
            }
            break;

        case STATE_PLAYING:
            updatePaddle(dt);
            updateBall(dt);
            drawPlayingScreen();
            break;

        case STATE_GAME_OVER:
            digitalWrite(PIN_LED_RED, HIGH); // Red LED stays on during Game Over
            drawGameOverScreen();
            if (currentMillis - stateStartTime > 5000) {
                digitalWrite(PIN_LED_RED, LOW);
                currentState = STATE_START_SCREEN;
                stateStartTime = currentMillis;
            }
            break;
            
        case STATE_WIN:
            drawWinScreen();
            if (currentMillis - stateStartTime > 5000) {
                currentState = STATE_START_SCREEN;
                stateStartTime = currentMillis;
            }
            break;
    }

    display.display();
}

void initGame() {
    lives = INITIAL_LIVES;
    digitalWrite(PIN_LED_RED, LOW);
    digitalWrite(PIN_LED_BLUE, LOW);
    resetLevel();
}

void resetLevel() {
    paddle.width = PADDLE_WIDTH;
    paddle.height = PADDLE_HEIGHT;
    paddle.x = (SCREEN_WIDTH - paddle.width) / 2.0f;
    paddle.y = SCREEN_HEIGHT - paddle.height - 2.0f;
    paddle.speed = PADDLE_SPEED;

    ball.radius = BALL_RADIUS;
    ball.x = paddle.x + paddle.width / 2.0f;
    ball.y = paddle.y - ball.radius - 1.0f;
    ball.velocity_x = 0;
    ball.velocity_y = 0;

    for (int r = 0; r < BLOCK_ROWS; r++) {
        for (int c = 0; c < BLOCK_COLS; c++) {
            blocks[r][c] = true;
        }
    }
}

void updatePaddle(float dt) {
    // Buttons flipped by user request
    if (digitalRead(PIN_BUTTON_1_LEFT) == LOW) {
        paddle.x += paddle.speed * dt; // Moved Right
    }
    if (digitalRead(PIN_BUTTON_2_CENTER) == LOW) {
        paddle.x -= paddle.speed * dt; // Moved Left
    }

    // Bound to screen
    if (paddle.x < 0) paddle.x = 0;
    if (paddle.x + paddle.width > SCREEN_WIDTH) paddle.x = SCREEN_WIDTH - paddle.width;
}

void updateBall(float dt) {
    ball.x += ball.velocity_x * dt;
    ball.y += ball.velocity_y * dt;

    // Wall collisions (Left and Right)
    if (ball.x - ball.radius < 0) {
        ball.x = ball.radius;
        ball.velocity_x *= -1;
    } else if (ball.x + ball.radius > SCREEN_WIDTH) {
        ball.x = SCREEN_WIDTH - ball.radius;
        ball.velocity_x *= -1;
    }

    // Wall collision (Top)
    if (ball.y - ball.radius < 0) {
        ball.y = ball.radius;
        ball.velocity_y *= -1;
    }

    // Paddle collision
    if (ball.velocity_y > 0 && 
        ball.y + ball.radius >= paddle.y && ball.y - ball.radius <= paddle.y + paddle.height &&
        ball.x + ball.radius >= paddle.x && ball.x - ball.radius <= paddle.x + paddle.width) {
        
        ball.y = paddle.y - ball.radius;
        ball.velocity_y *= -1;
        
        // Add "english" to the ball based on where it hit the paddle
        float hitFactor = (ball.x - (paddle.x + paddle.width / 2.0f)) / (paddle.width / 2.0f);
        ball.velocity_x = hitFactor * BALL_SPEED_BASE * 1.5f; 
    }

    // Block collision
    bool blockHit = false;
    bool allCleared = true;
    for (int r = 0; r < BLOCK_ROWS; r++) {
        for (int c = 0; c < BLOCK_COLS; c++) {
            if (blocks[r][c]) {
                allCleared = false;
                float bx = c * BLOCK_WIDTH;
                float by = BLOCK_START_Y + r * BLOCK_HEIGHT;
                
                // Simple AABB bounding box check
                if (ball.x + ball.radius >= bx && ball.x - ball.radius <= bx + BLOCK_WIDTH &&
                    ball.y + ball.radius >= by && ball.y - ball.radius <= by + BLOCK_HEIGHT) {
                    
                    blocks[r][c] = false;
                    blockHit = true;
                    
                    // Simple bounce: reverse Y velocity
                    // For a more advanced game, we'd check which side was hit.
                    ball.velocity_y *= -1; 
                }
            }
        }
    }

    if (blockHit) {
        digitalWrite(PIN_LED_BLUE, HIGH);
        blueLedTurnOffTime = millis() + 50; // Flash Blue LED for 50ms
    }
    
    if (allCleared) {
        currentState = STATE_WIN;
        stateStartTime = millis();
    }

    // Lose life condition (ball falls off screen)
    if (ball.y - ball.radius > SCREEN_HEIGHT) {
        lives--;
        digitalWrite(PIN_LED_RED, HIGH);
        
        if (lives > 0) {
            currentState = STATE_SERVE_WAIT;
            stateStartTime = millis();
            redLedTurnOffTime = millis() + 1000; // Red LED stays on for 1 second to emphasize life lost
            
            // Reset paddle and ball positions
            paddle.x = (SCREEN_WIDTH - paddle.width) / 2.0f;
            ball.x = paddle.x + paddle.width / 2.0f;
            ball.y = paddle.y - ball.radius - 1.0f;
            ball.velocity_x = 0;
            ball.velocity_y = 0;
        } else {
            currentState = STATE_GAME_OVER;
            stateStartTime = millis();
        }
    }
}

void drawStartScreen() {
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(20, 10);
    display.println(F("BLOCK"));
    display.setCursor(10, 30);
    display.println(F("BREAKER"));
    
    display.setTextSize(1);
    display.setCursor(20, 50);
    display.println(F("Press to Start"));
}

void drawPlayingScreen() {
    // Draw Paddle
    display.fillRect((int)paddle.x, (int)paddle.y, (int)paddle.width, (int)paddle.height, SSD1306_WHITE);
    
    // Draw Ball
    display.fillCircle((int)ball.x, (int)ball.y, (int)ball.radius, SSD1306_WHITE);
    
    // Draw Blocks
    for (int r = 0; r < BLOCK_ROWS; r++) {
        for (int c = 0; c < BLOCK_COLS; c++) {
            if (blocks[r][c]) {
                display.fillRect(c * BLOCK_WIDTH + 1, BLOCK_START_Y + r * BLOCK_HEIGHT + 1, BLOCK_WIDTH - 2, BLOCK_HEIGHT - 2, SSD1306_WHITE);
            }
        }
    }

    // Draw Lives
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.print(F("LIVES: "));
    display.print(lives);
}

void drawGameOverScreen() {
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 25);
    display.println(F("GAME OVER"));
}

void drawWinScreen() {
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(15, 25);
    display.println(F("YOU WIN!"));
}
