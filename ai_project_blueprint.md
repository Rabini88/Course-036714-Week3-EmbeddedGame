# Embedded Systems Game Project - Final Blueprint

## 1. Detailed Hardware Inventory
* **Brain: ESP32 Development Board (ESP-WROOM-32)**
  * *Details:* 38-pin variant, 3.3V logic level. Features a dual-core processor, built-in Wi-Fi/Bluetooth, and a CP2102 USB-to-UART bridge for programming. Acts as the central logic controller.
* **Display: 0.96" OLED Module**
  * *Details:* 128x64 pixel monochrome screen driven by the SSD1306 controller. Uses the I2C protocol requiring only 4 pins: `GND`, `VCC` (3.3V/5V compatible), `SCL` (Serial Clock), and `SDA` (Serial Data). Hardware address is usually `0x3C`.
* **Inputs: 3x Tactile Push Buttons**
  * *Details:* Momentary (Normally Open) switches with 4 pins (internally shorted in pairs). Best wired using the ESP32's internal pull-up resistors (`INPUT_PULLUP`), requiring only a connection to a GPIO pin and Ground, completely eliminating the need for external resistors.
* **Outputs (Visual): 1x Red LED, 1x Blue LED**
  * *Details:* Standard 5mm through-hole LEDs. Polarity sensitive: the longer leg (anode) goes to the GPIO signal, and the shorter leg (cathode/flat edge) goes to ground. *(Warning: Running these directly from a 3.3V pin without a current-limiting resistor is risky and could burn them out over time).*
* **Outputs (Audio): 1x Active Buzzer (TMB12A05)**
  * *Details:* Generates its own continuous loud tone when driven HIGH (no complex PWM signals needed). Polarity sensitive: the longer leg (and side marked with the '+' sticker) connects to the ESP32 signal pin, shorter leg to ground.
* **Infrastructure: 400-Point Solderless Breadboard**
  * *Details:* Standard half-size breadboard featuring twin power rails (red/blue) on each side and a central terminal strip. Used to distribute power and ground safely to all components without soldering.
* **Cabling: Dupont Jumper Wires**
  * *Details:* Male-to-Male wires for routing connections entirely on the breadboard. Male-to-Female wires for connecting the male headers of the OLED screen directly to the breadboard or ESP32 pins.
* **Power/Data: Micro-USB Cable**
  * *Details:* Provides 5V power from your computer and serves as the serial data link to flash compiled code from VS Code to the ESP32 chip.

## 2. Game Concepts & Architectures
Here are five classic, generic game concepts designed specifically for this hardware layout:

* **Concept 1: Classic Sequence Memory (Simon Says)**
  * *Mechanic:* The OLED displays a prompt and the LEDs flash in a specific sequence. The user must use the three buttons to repeat the sequence perfectly. The sequence grows longer each round.
  * *Feedback:* The OLED tracks the current score and high score. The buzzer plays a pleasant tone for correct inputs and a harsh buzz for a mistake.

* **Concept 2: Reflex Target Practice (Whack-a-Mole Style)**
  * *Mechanic:* Three columns or targets appear on the OLED, corresponding to the three buttons. Targets randomly appear and disappear in the columns. The player must press the correct button before the target vanishes.
  * *Feedback:* Game speed increases over time. Blue LED flashes for hits, Red LED for misses.

* **Concept 3: 2D Endless Runner (Survival Platformer)**
  * *Mechanic:* A simple 2D side-scrolling game on the OLED (similar to the offline browser dinosaur game). The player controls a small block. One button jumps over ground obstacles, another ducks under flying obstacles.
  * *Feedback:* The buzzer plays short beeps for jumps. The OLED tracks distance traveled as the score.

* **Concept 4: Digital Safecracker (Logic/Code Puzzle)**
  * *Mechanic:* The player must guess a hidden 3-digit combination. They use two buttons to cycle numbers up and down, and the third button to submit the guess.
  * *Feedback:* The OLED displays the guesses and gives "Mastermind" style feedback (e.g., showing how many numbers are correct and in the right position). The buzzer ticks like a timer to add pressure.

* **Concept 5: Single-Player Pong (Wall Ball)**
  * *Mechanic:* A paddle sits on one side of the OLED screen, defending against a ball bouncing off the other three walls. The player uses two buttons to move the paddle UP and DOWN. The third button serves the ball or acts as a pause menu. As the score increases, the ball's movement speed scales up.
  * *Feedback:* The buzzer emits a short "boop" when the ball strikes the paddle or a wall, and a low, sad "buzz" if the ball gets past the paddle. The LEDs flash rapidly when a new high score is reached.

## 3. Next Steps for VS Code Setup
1. Set up the PlatformIO extension in VS Code.
2. Install the `Adafruit SSD1306` and `Adafruit GFX` libraries to drive the OLED.
3. Wire the OLED using the standard I2C pins (SDA -> GPIO 21, SCL -> GPIO 22).
4. Wire the buttons directly to ground and use the ESP32's internal pull-up resistors (`INPUT_PULLUP` in code) to keep your breadboard wiring clean.
