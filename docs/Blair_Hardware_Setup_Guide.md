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

### 2. The Three Buttons (Inputs)
* **Placement:** The 4-pin tactile buttons will straddle the center trench in the lower half of the board (where all columns are open).
  * **Button 1 (Left Action):** Insert into rows **22 and 24** (pins into `e22`, `e24` and `f22`, `f24`).
  * **Button 2 (Center Action):** Insert into rows **25 and 27** (pins into `e25`, `e27` and `f25`, `f27`).
  * **Button 3 (Right Action):** Insert into rows **28 and 30** (pins into `e28`, `e30` and `f28`, `f30`).
* **Wiring:** 
  * **Grounding:** Connect a jumper wire from the right Blue (-) rail to the top-right pin of each button (`j22`, `j25`, `j28` - note: just connect any hole in rows 22, 25, 28 on the right side to the Blue rail).
  * **Signal:** Connect a jumper wire from the bottom-right pin of each button to the ESP32 via column `j`:
    * Button 1 signal (`i24`) -> **ESP32 GPIO 12 (plug into `j7`)**
    * Button 2 signal (`i27`) -> **ESP32 GPIO 13 (plug into `j5`)**
    * Button 3 signal (`i30`) -> **ESP32 GPIO 14 (plug into `j8`)**

### 3. LEDs (Visual Outputs) - JUMPER-LESS DESIGN
* **Hack:** Since we are low on jumper wires, we will plug the LEDs *directly* into the ESP32's signal pins and the ground rail! The LED legs are flexible enough to span the gap.
* **Red LED (Game Over/Miss):**
  * Insert the long leg (Anode) directly into **`j11`** (ESP32 GPIO 25).
  * Stretch the short leg (Cathode) over and insert it directly into the right **Blue (-)** power rail at row 11.
* **Blue LED (Hit/Score):**
  * Insert the long leg (Anode) directly into **`j10`** (ESP32 GPIO 26).
  * Stretch the short leg (Cathode) over and insert it directly into the right **Blue (-)** power rail at row 10.

### 4. Active Buzzer (Audio Output) - REMOTE PLACEMENT
* **Hack:** Since the buzzer is physically bulky, it cannot sit directly at `j9` without colliding with the LEDs and button wires. We will use your 2 remaining **Male-to-Male** jumper wires to place it out of the way.
* **Placement:** Place the buzzer in the bottom-left corner of the breadboard.
  * Insert the long leg (`+`) into **`a27`**.
  * Insert the short leg (`-`) into **`a29`**.
* **Wiring (Using 2 M-M jumpers):**
  * **Grounding:** Connect a jumper wire from **`b29`** (or any hole in row 29 on the left side) to the nearest **Blue (-)** power rail (you can run it over the trench to the right Blue rail).
  * **Signal:** Connect a jumper wire from **`b27`** back to **ESP32 GPIO 27 (plug into `j9`)**.

### 5. OLED Display (I2C)
* **Placement:** Do not mount this directly on the crowded breadboard. Use four **Male-to-Female** Dupont jumper wires to connect the OLED's male header pins.
* **Wiring:**
  * `GND` -> Right Blue (-) rail.
  * `VCC` -> Right Red (+) rail (3.3V).
  * `SCL` -> **ESP32 GPIO 33 (plug into `j12`)** (Remapped to the right side!)
  * `SDA` -> **ESP32 GPIO 32 (plug into `j13`)** (Remapped to the right side!)

---
## Next Steps
Once you have physically connected all these components according to the exact coordinates above, please confirm. The next step will be to write a minimal hardware test script to verify that the buttons read correctly, the LEDs blink, the buzzer sounds, and the OLED initializes successfully.
