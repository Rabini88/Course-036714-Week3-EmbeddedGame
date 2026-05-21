# Embedded Systems Game Project - Final Blueprint

## 1. Detailed Hardware Inventory
* **Brain: ESP32 Development Board (ESP-WROOM-32)**
  * *Details:* 38-pin variant, 3.3V logic level. Features a dual-core processor, built-in Wi-Fi/Bluetooth, and a CP2102 USB-to-UART bridge for programming.
* **Display: 0.96" OLED Module**
  * *Details:* 128x64 pixel monochrome screen driven by the SSD1306 controller. Uses the I2C protocol requiring only 4 pins: `GND`, `VCC` (3.3V/5V compatible), `SCL` (Serial Clock), and `SDA` (Serial Data). Hardware address is usually `0x3C`.
* **Inputs: 2x Tactile Push Buttons**
  * *Details:* Momentary (Normally Open) switches with 4 pins. Best wired using the ESP32's internal pull-up resistors (`INPUT_PULLUP`), requiring only a connection to a GPIO pin and Ground. We have Left and Center buttons (Right was removed).
* **Outputs (Visual): 1x Red LED, 1x Blue LED**
  * *Details:* Standard 5mm through-hole LEDs. Polarity sensitive (longer leg = anode/positive, shorter flat leg = cathode/ground). 
* **Outputs (Audio): None**
  * *Details:* The active buzzer was removed to free up wiring for the OLED display.
* **Infrastructure: 400-Point Solderless Breadboard**
  * *Details:* Standard half-size breadboard.
* **Cabling: Dupont Jumper Wires**
  * *Details:* Male-to-Male wires and Male-to-Female wires.
* **Power/Data: Micro-USB Cable**
  * *Details:* Provides 5V power and serves as the serial data link for flashing code.

## 2. Breadboard Pinout Mapping (CRITICAL CONSTRAINTS)
**Hardware Reality:** The ESP32 is wide and is seated in breadboard columns `b` and `i`, spanning rows `1` through `19`. 
**Wiring Constraint:** You ONLY have **column `a`** (left side) and **column `j`** (right side) available for jumper wires. All connections must be routed through these single available holes.

| Breadboard Row | Left Side Access (Col `a`) | Right Side Access (Col `j`) | Wiring Notes & Best Uses |
| :--- | :--- | :--- | :--- |
| **1 (Top - USB)**| `CLK` | `V5` (5V / VIN) | 5V Power available on the right |
| **2** | `SD0` | `CMD` | *Avoid using SD pins (used for internal flash)* |
| **3** | `SD1` | `SD3` | *Avoid using SD pins* |
| **4** | `G15` | `SD2` | *Avoid using SD pins* |
| **5** | `G2` | `G13` | Safe GPIOs |
| **6** | `G0` | `GND` | Ground available on the right |
| **7** | `G4` | `G12` | Safe GPIOs |
| **8** | `G16` | `G14` | Safe GPIOs |
| **9** | `G17` | `G27` | Safe GPIOs |
| **10** | `G5` | `G26` | Safe GPIOs |
| **11** | `G18` | `G25` | Safe GPIOs |
| **12** | `G19` | `G33` | Safe GPIOs |
| **13** | `GND` | `G32` | Ground available on the left |
| **14** | **`G21` (SDA)**| `G35` | **OLED I2C SDA (Left)** / Input Only (Right) |
| **15** | `RXD` | `G34` | Input Only (Right) |
| **16** | `TXD` | `SN` (GPIO 39) | Input Only (Right) |
| **17** | **`G22` (SCL)**| `SP` (GPIO 36) | **OLED I2C SCL (Left)** / Input Only (Right) |
| **18** | `G23` | `EN` | Safe GPIO (Left) |
| **19 (Bottom)**| `GND` | `3V3` (3.3V) | Ground (Left) / 3.3V Power available (Right) |

## 3. Game Concepts & Architectures
Here is the chosen game concept designed specifically for this 2-button hardware layout:

* **Concept: Block Breaker (Breakout / Arkanoid Style)**
  * *Mechanic:* A paddle at the bottom of the OLED screen defends against a bouncing ball that destroys bricks at the top of the screen.
  * *Controls:* The two available tactile buttons (Left and Center) will move the paddle LEFT and RIGHT respectively.
  * *Visual Feedback:* The Blue LED will flash briefly when the ball hits a brick or the paddle. The Red LED will light up (and potentially flash) when the ball falls past the paddle (Game Over/Miss).
  * *Auto-Serve:* Since we only have two buttons and no dedicated "Serve" button, the ball will automatically serve after a short delay when a new game starts or a life is lost.
  * **Detailed Specs:** See [`docs/game_specifications.md`](game_specifications.md) for full architectural guidelines, state machine details, and performance requirements (e.g., 400kHz I2C, non-blocking loops).

## 4. Next Steps for VS Code / Antigravity Setup
1. Open this workspace in the Antigravity IDE.
2. Prompt the Agent: *"Read `@ai_project_blueprint.md`. I want to build [Insert Concept Number]. Please initialize a PlatformIO project for the ESP32. Pay strict attention to Section 2: you must map your code to use the accessible pins listed there."*
3. The agent will read the pinout table to ensure it only uses GPIOs that you can actually physically wire up.
