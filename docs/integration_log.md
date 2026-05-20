# Physical Integration Log
*A living document tracking the physical hardware setup and wiring progress.*

## [2026-05-20] Step 1: ESP32 Brain Insertion
**Status:** Completed

* **Action:** Inserted the ESP32-WROOM-32 (38-pin variant) into the 400-point breadboard and pushed it down firmly.
* **Location:** Rows 1 to 19.

## [2026-05-20] Step 2: Power Rails Wiring
**Status:** Completed

* **Action:** Wire the 3.3V and GND pins of the ESP32 to the breadboard's right-side power rails.
* **Expected Connections:**
  * `3V3` (j19) -> Right Red (+) rail
  * `GND` (j6) -> Right Blue (-) rail

## [2026-05-20] Step 3: The Three Tactile Buttons
**Status:** Completed

* **Action:** Placed the three tactile buttons across the center trench and wired them to ground and signal pins.
* **Button Placement:**
  * **Left:** Rows 22 and 24 (`e/f` columns)
  * **Center:** Rows 25 and 27 (`e/f` columns)
  * **Right:** Rows 28 and 30 (`e/f` columns)
* **Expected Connections:**
  * **Grounds:** `j22` -> Blue (-), `j25` -> Blue (-), `j28` -> Blue (-)
  * **Signals:** 
    * `i24` -> `j7` (GPIO 12)
    * `i27` -> `j5` (GPIO 13)
    * `i30` -> `j8` (GPIO 14)

## [2026-05-20] Step 4: LEDs (Visual Outputs) - JUMPER-LESS DESIGN
**Status:** Completed

* **Action:** Plugged LEDs directly into the ESP32 GPIO pins and the ground rail to save jumper wires.
* **Expected Connections:**
  * **Red LED:** Long leg -> `j11` (GPIO 25), Short leg -> Right Blue (-) rail at row 11
  * **Blue LED:** Long leg -> `j10` (GPIO 26), Short leg -> Right Blue (-) rail at row 10

## [2026-05-20] Step 5: Active Buzzer - REMOTE PLACEMENT
**Status:** Paused (Pending Phase 1 Software Test)

* **Action:** Physical assembly of the Buzzer and OLED is temporarily paused to allow for incremental software testing of the Buttons and LEDs.
* **Buzzer Placement:**
  * **Long leg (+):** `a27`
  * **Short leg (-):** `a29`
* **Expected Connections:**
  * **Ground:** Jumper from `b29` to Right Blue (-) rail
  * **Signal:** Jumper from `b27` to `j9` (GPIO 27)
