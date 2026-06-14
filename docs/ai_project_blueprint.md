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
**Hardware Reality:** The ESP32 is seated in breadboard column `b`, but it is **rotated 180 degrees (upside down)**. 
**Wiring Constraint:** You ONLY have **column `a`** (left side) available for jumper wires. The right side of the ESP32 is "in the air" and not plugged into the breadboard.

| Breadboard Row | Left Side Access (Col `a`) | Wiring Notes & Best Uses |
| :--- | :--- | :--- |
| **1 (Top)** | `GND` | Ground available on the left |
| **2** | `G23` | Safe GPIO |
| **3** | `G22` (SCL) | **OLED I2C SCL** |
| **4** | `TXD` | TX |
| **5** | `RXD` | RX |
| **6** | `G21` (SDA) | **OLED I2C SDA** |
| **7** | `GND` | Ground available on the left |
| **8** | `G19` | Safe GPIO (Buzzer) |
| **9** | `G18` | Safe GPIO (Left Button) |
| **10** | `G5` | Safe GPIO |
| **11** | `G17` | Safe GPIO (Right Button) |
| **12** | `G16` | Safe GPIO |
| **13** | `G4` | Safe GPIO |
| **14** | `G0` | Safe GPIO |
| **15** | `G2` | Safe GPIO |
| **16** | `G15` | Safe GPIO |
| **17** | `SD1` | *Avoid using SD pins (used for internal flash)* |
| **18** | `SD0` | *Avoid using SD pins* |
| **19 (Bottom)**| `CLK` | *Avoid using CLK* |

*Note: The right-side pins (e.g., 3V3) must be connected via direct Female-to-Male jumpers since they are not on the breadboard.*

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
