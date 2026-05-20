# Physical Integration Log
*A living document tracking the physical hardware setup and wiring progress.*

## [2026-05-20] Step 1: ESP32 Brain Insertion
**Status:** In Progress / Needs Adjustment

* **Action:** Inserted the ESP32-WROOM-32 (38-pin variant) into the 400-point breadboard.
* **Location:** Rows 1 to 19.
* **Observations (from Integration Photos):**
  1. **Depth:** The ESP32 is currently sitting very high on its pins. The yellow plastic base of the header pins is completely visible above the breadboard. It is not fully seated.
  2. **Width & Columns:** The ESP32 board is very wide and is currently sitting from column `a` to `i`, leaving only `j` free. 
* **Next Steps / Adjustments Required:**
  * **DO NOT MOVE THE BOARD:** The board's specific pinout has the critical `3V3` power pin on the RIGHT side (`j19`). Leaving column `j` free is actually the correct configuration. We will use the right side exclusively for all our wiring.
  * **Push it down firmly:** Apply firm, even pressure to push it down until the plastic headers are almost flush with the breadboard.
  * **Wiring Update:** All components (buttons, LEDs, OLED) will be re-mapped to use the available GPIOs on the right side of the board (accessed via column `j`).
