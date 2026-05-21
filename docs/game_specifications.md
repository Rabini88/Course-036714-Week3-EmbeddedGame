# Game Specifications: Block Breaker

**Version:** 1.0
**Author:** Alex (Game Designer), with inputs from Charlie, Val, and Blair

---

## 1. Core Concept (Alex - Game Designer)
**Title:** Block Breaker
**Genre:** Arcade (Breakout / Arkanoid clone)
**Platform:** ESP32 with 128x64 Monochrome OLED

### 1.1 Gameplay Loop
* The player controls a paddle at the bottom of the screen to bounce a ball upwards.
* The ball destroys blocks arranged at the top of the screen upon collision.
* If the ball falls past the paddle (bottom of the screen), the player loses a life.
* The game ends when all lives are lost (Game Over) or all blocks are cleared (Win).

### 1.2 Controls
* **Left Button (Pin 18):** Moves the paddle left.
* **Right/Center Button (Pin 19):** Moves the paddle right.
* *Constraint:* Because we only have two buttons, there is no dedicated "Serve" or "Start" button. The game will rely on auto-serving.

### 1.3 Game Flow & States
* **Start Screen:** Displays the game title. After 3 seconds (or any button press), transitions to playing.
* **Playing:** The ball rests on the paddle for 2 seconds (giving the player time to prepare), then auto-serves upwards.
* **Game Over / Win Screen:** Displays the result. Resets to the Start Screen after 5 seconds.

### 1.4 Visual & Physical Feedback
* **Screen:** High-framerate rendering of the paddle, ball, and blocks.
* **Blue LED:** Flashes rapidly (e.g., 50ms) whenever the ball strikes a block. This adds "punch" to the impacts.
* **Red LED:** Turns on solid when a life is lost. Stays on during the Game Over screen to draw the player's eye.

---

## 2. Technical Architecture (Charlie - Software Architect)

### 2.1 State Machine
The main loop will be driven by a finite state machine to keep the code modular:
```cpp
enum GameState {
    STATE_START_SCREEN,
    STATE_SERVE_WAIT,
    STATE_PLAYING,
    STATE_GAME_OVER,
    STATE_WIN
};
```

### 2.2 Entity Structures
We will use structs or lightweight classes for the game entities.
* `Paddle`: Needs `x, y, width, height, speed`.
* `Ball`: Needs `x, y, radius, velocity_x, velocity_y`. **Crucial:** Position and velocity must use `float` types for smooth sub-pixel movement. If we use integers, the ball will only move in rigid 45-degree angles.
* `BlockMap`: A 2D array of booleans representing active/destroyed blocks.

### 2.3 Non-Blocking Game Loop
The `delay()` function is banned from the `loop()`. The entire game must run on a `millis()` delta-time architecture to ensure input is always responsive.

---

## 3. Resource & Performance Optimization (Val - Resource Optimizer)

### 3.1 I2C Speed
The standard I2C clock is 100kHz, which takes too long to push a 128x64 buffer (1024 bytes) to the OLED. We must increase the I2C speed to 400kHz immediately after `Wire.begin()`:
`Wire.setClock(400000);`
This is critical for achieving a playable framerate (targeting 30-60 FPS).

### 3.2 Display Rendering
Given the ESP32's processing power, we have enough RAM to use the `Adafruit_GFX` full buffer (`display.display()`). We will clear the buffer and redraw everything every frame. If performance drops, we will optimize to dirty-rect rendering, but a full redraw is the cleanest starting point.

### 3.3 Block Storage
For a 128x64 screen, a good block layout is 8 columns by 4 rows (32 blocks). This can be stored in a simple 1D or 2D array of `bool` or `uint8_t`.

---

## 4. Hardware Integration (Blair - Embedded Engineer)

### 4.1 Software Debouncing
Tactile buttons bounce. If we read them raw, a single press might register multiple times, causing the paddle to jitter. We must implement software debouncing or simply read the pin state every frame (since movement is continuous). For continuous movement, `digitalRead() == LOW` every frame is acceptable, but state transitions (like "Press to Start") require a debounce check.

### 4.2 Asynchronous LED Control
Flashing the Blue LED cannot use `delay()`. If we `delay(50)` to flash the LED when a block breaks, the entire game pauses for 50ms, causing massive visual stuttering on the OLED.
*Solution:* Set a variable `unsigned long blueLedTurnOffTime = millis() + 50;` when the hit occurs, and turn on the LED. In the main loop, check `if (millis() > blueLedTurnOffTime)` to turn it off.

### 4.3 Pin Defs
All hardware interactions MUST continue to reference `config.h`. No hardcoded `digitalWrite(4, HIGH)`.
