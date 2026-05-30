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
* **Placement:** Keep the ESP32 exactly where it is (Rows 1 to 19). The left pins are in column `a` and the right pins are in column `i`. This blocks the left side but leaves **column `j` completely free** for all our wiring. Ensure the Micro-USB port is pointing outwards at the top. 
* **Power:** 
  * Connect a jumper wire from the ESP32 `3V3` pin (located at **`j19`**) to the **Red (+)** power rail on the right side.
  * Connect a jumper wire from an ESP32 `GND` pin (located at **`j6`**) to the **Blue (-)** power rail on the right side.
  * *Note: All components will use this right Blue (-) rail for ground.*

### 2. The Two Buttons (Inputs)
* **Placement:** The 4-pin tactile buttons will straddle the center trench in the lower half of the board.
  * **Button 1 (Right Action - physically on left):** Insert into rows **21 and 23** (pins into `e21`, `e23` and `f21`, `f23`).
  * **Button 2 (Left Action - physically on right):** Insert into rows **24 and 26** (pins into `e24`, `e26` and `f24`, `f26`).
* **Wiring:** 
  * **Grounding:** Connect a jumper wire from the right Blue (-) rail to the top-right pin of each button (`j21`, `j24`).
  * **Signal:** Connect a jumper wire from the bottom-right pin of each button to the ESP32 via column `j`:
    * Button 1 signal (`i23`) -> **ESP32 GPIO 12 (plug into `j7`)**
    * Button 2 signal (`i26`) -> **ESP32 GPIO 13 (plug into `j5`)**

### 3. LEDs (Visual Outputs) - JUMPER-LESS DESIGN
* **Hack:** Since we are low on jumper wires, we will plug the LEDs *directly* into the ESP32's signal pins and the ground rail! The LED legs are flexible enough to span the gap.
* **Red LED (Game Over/Miss):**
  * Insert the long leg (Anode) directly into **`j11`** (ESP32 GPIO 25).
  * Stretch the short leg (Cathode) over and insert it directly into the right **Blue (-)** power rail at row 11.
* **Blue LED (Hit/Score):**
  * Insert the long leg (Anode) directly into **`j10`** (ESP32 GPIO 26).
  * Stretch the short leg (Cathode) over and insert it directly into the right **Blue (-)** power rail at row 10.

### 4. OLED Display (I2C) - DIRECT BREADBOARD MOUNT
* **Placement:** Plug the OLED header pins directly into the left side of the breadboard (column `a`) at the bottom.
  * Pin 1 (GND) -> `a27`
  * Pin 2 (VCC) -> `a28`
  * Pin 3 (SCL) -> `a29`
  * Pin 4 (SDA) -> `a30`
* **Wiring (Use Male-to-Male jumper wires):**
  * **GND:** Connect `b27` to the right **Blue (-)** power rail.
  * **VCC:** Connect `b28` to the right **Red (+)** power rail.
  * **SCL:** Connect `b29` to **ESP32 GPIO 33 (plug into `j12`)**.
  * **SDA:** Connect `b30` to **ESP32 GPIO 32 (plug into `j13`)**.

---
## Next Steps
Once you have physically connected all these components according to the exact coordinates above, the hardware is complete! The codebase now features the fully playable Block Breaker game with flipped controls, a non-blocking rendering loop, and tweaked game parameters. The project is officially complete!
