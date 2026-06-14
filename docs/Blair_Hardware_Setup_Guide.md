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

## Precise Breadboard Layout & Connections (UPDATED)

*Note: The breadboard has rows numbered 1 to 30. Columns a-e are on the left of the center trench, and f-j are on the right.*

### 1. The ESP32 Brain & Power Rails
* **Placement:** The ESP32 is seated in breadboard column `b` but is **rotated 180 degrees (upside down)**. The right-side pins of the ESP32 are "in the air" and not plugged into the breadboard. All accessible pins are on the left side (access via column `a`), but mapped in reverse (Row 19 is now Row 1).
* **Power:** 
  * **3V3:** Requires a direct Female-to-Male jumper from the 3V3 pin "in the air" to the component.
  * **GND:** Accessible at breadboard row 1 (`a1`/`b1`/`c1`/`d1`) and row 7 (`a7`/`b7`).

### 2. The OLED Display (I2C)
* **Placement:** The OLED header pins are plugged directly into the right side of the breadboard at the top (column `j`, rows 1-4).
* **Wiring:**
  * Row 1 (`j1` / SDA) -> Jumper to **ESP32 GPIO 21** (`a6`)
  * Row 2 (`j2` / SCL) -> Jumper to **ESP32 GPIO 22** (`a3`)
  * Row 3 (`j3` / VCC) -> Female-to-Male jumper to **ESP32 3V3** (in the air)
  * Row 4 (`j4` / GND) -> Jumper to **GND** (e.g., `b2`)

### 3. The Two Buttons (Inputs)
* **Wiring:** 
  * **Right Button (Button 1):** 
    * Signal: Row 20 -> Jumper to **ESP32 GPIO 17** (`a11`)
    * Ground: Row 22 -> Jumper to **GND** (`b7`)
  * **Left Button (Button 2):**
    * Signal: Row 23 -> Jumper to **ESP32 GPIO 18** (`a9`)
    * Ground: Row 25 -> Jumper to **GND** (`d1`)

### 4. Buzzer (Output)
* **Placement:** Straddling the bottom of the board at Row 30.
* **Wiring:**
  * **Positive Leg (`f30`):** `j30` -> Jumper to **ESP32 GPIO 19** (`a8`)
  * **Negative Leg (`e30`):** `a30` -> Jumper to **GND** (`c1`)

### 5. LEDs (Visual Outputs)
* **Status:** Currently unplugged. Disabled in physical layout but kept in logic structure.

---

## Flashing Code via Terminal (PowerShell)

To compile and load the firmware onto the ESP32 using the command line:

1. **Configure Environment for UTF-8 Compatibility:**
   Set the Python encoding environment variable in your PowerShell terminal to avoid encoding errors caused by Hebrew characters in the directory path:
   ```powershell
   $env:PYTHONUTF8=1
   ```

2. **Navigate to the Project Root Directory:**
   ```powershell
   cd "c:\Users\leeor\OneDrive - Technion\Studies_Masters\Courses\סמסטר ז' - אביב 2026\036714 - שימושים ופיתוח בעזרת בינה מלאכותית בהובלת מומחה\Week 3\Course-036714-Week3-EmbeddedGame"
   ```

3. **Build and Upload the Code:**
   Ensure your ESP32 is plugged into your PC via USB, then run:
   ```powershell
   pio run -t upload
   ```

4. **Open the Serial Monitor (Optional):**
   To check real-time debugging output and serial logs:
   ```powershell
   pio device monitor
   ```

---

## Next Steps
Once you have physically connected all these components according to the exact coordinates above, the hardware is complete! The codebase now features the fully playable Block Breaker game with flipped controls, a non-blocking rendering loop, and tweaked game parameters. The project is officially complete!
