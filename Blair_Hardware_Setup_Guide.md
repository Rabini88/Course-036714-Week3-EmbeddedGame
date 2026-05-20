# Hardware Setup & Wiring Guide
**Prepared by the Virtual Expert Team**

## Expert Opinions & Mandates

**Blair (Embedded Engineer):** 
"We need to wire this up carefully. Always establish your common ground first. Since we are lacking physical current-limiting resistors for the LEDs, we will rely on the 3.3V logic level and avoid keeping them on continuously at full brightness to prevent burnout. For the buttons, wire them directly to ground—we will use `INPUT_PULLUP` in code to save space and reduce wiring complexity."

**Alex (Game Designer):**
"Make sure the three buttons are spaced out so they feel like a natural D-pad or action cluster. Position the OLED using the jumper wires so it can face the player directly without their hands blocking the screen during gameplay."

**Charlie (Software Architect):**
"As you connect these components, stick to the exact GPIO pins we define here. I will map these exact pins in a `config.h` file later so our codebase remains modular and clean."

**Val (Resource Optimizer):**
"Connect the hardware exactly as described, but we will test it incrementally. We'll write a simple test script first to verify the connections before loading any complex game logic. This saves us from debugging hardware and software simultaneously."

---

## Precise Breadboard Layout & Connections

*Note: The breadboard has rows numbered 1 to 30. Columns a-e are on the left of the center trench, and f-j are on the right. Power rails are on the far edges (Red for +, Blue for -).*

### 1. The ESP32 Brain & Power Rails
* **Placement:** Carefully insert the ESP32 into the top of the breadboard (Rows 1 to 19), straddling the center trench. Ensure the Micro-USB port is pointing outwards at the top. 
* **Power:** 
  * Connect a jumper wire from an ESP32 `3V3` pin to the **Red (+)** power rail on the left.
  * Connect a jumper wire from an ESP32 `GND` pin to the **Blue (-)** power rail on the left.
  * *Note: All components will use this left Blue (-) rail for ground.*

### 2. The Three Buttons (Inputs)
* **Placement:** The 4-pin tactile buttons will straddle the center trench in the lower half of the board.
  * **Button 1 (Left Action):** Insert into rows **21 and 23** (pins into `e21`, `e23` and `f21`, `f23`).
  * **Button 2 (Center Action):** Insert into rows **25 and 27** (pins into `e25`, `e27` and `f25`, `f27`).
  * **Button 3 (Right Action):** Insert into rows **28 and 30** (pins into `e28`, `e30` and `f28`, `f30`).
* **Wiring:** 
  * **Grounding:** Connect a jumper wire from the left Blue (-) rail to the top-left pin of each button (`a21`, `a25`, `a28`).
  * **Signal:** Connect a jumper wire from the top-right pin of each button to the ESP32. (Locate the corresponding GPIO pins on the rows alongside the ESP32):
    * Button 1 (`j21`) -> **ESP32 GPIO 12**
    * Button 2 (`j25`) -> **ESP32 GPIO 13**
    * Button 3 (`j28`) -> **ESP32 GPIO 14**

### 3. LEDs (Visual Outputs)
* **Placement:** We will place these on the left side of the lower board.
  * **Red LED:** Insert the long leg (Anode) into `b21` and the short leg (Cathode) into `b22`.
  * **Blue LED:** Insert the long leg (Anode) into `b25` and the short leg (Cathode) into `b26`.
* **Wiring:**
  * **Grounding:** Connect `a22` (Red Cathode) and `a26` (Blue Cathode) to the left Blue (-) rail.
  * **Signal:**
    * Connect `c21` (Red Anode) to **ESP32 GPIO 25**
    * Connect `c25` (Blue Anode) to **ESP32 GPIO 26**

### 4. Active Buzzer (Audio Output)
* **Placement:** Place on the right side of the lower board.
  * Insert the long leg (marked with `+`) into `i21`.
  * Insert the short leg (`-`) into `i22`.
* **Wiring:**
  * **Grounding:** Connect a jumper from `j22` directly to the left Blue (-) rail.
  * **Signal:** Connect a jumper from `j21` to **ESP32 GPIO 27**.

### 5. OLED Display (I2C)
* **Placement:** Do not mount this directly on the crowded breadboard. Use four **Male-to-Female** Dupont jumper wires to connect the OLED's male header pins.
* **Wiring:**
  * `GND` -> Left Blue (-) rail.
  * `VCC` -> Left Red (+) rail (3.3V).
  * `SCL` -> **ESP32 GPIO 22**
  * `SDA` -> **ESP32 GPIO 21**

---
## Next Steps
Once you have physically connected all these components according to the exact coordinates above, please confirm. The next step will be to write a minimal hardware test script to verify that the buttons read correctly, the LEDs blink, the buzzer sounds, and the OLED initializes successfully.
