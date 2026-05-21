# Physical Integration Log
*A living document tracking the physical hardware setup and wiring progress.*

---

## Hardware Inventory (Verified 2026-05-20)
| Cable Type | Quantity |
|---|---|
| Male-to-Male (M-M) | 10 |
| Male-to-Female (M-F) | 2 |

---

## Cable Budget Plan

| Step | Component | Wires | Type | Running Total (M-M) |
|---|---|---|---|---|
| Step 2 | Power Rails (3V3 + GND) | 2 | M-M | 2 |
| Step 3 | Button Grounds (×2) | 2 | M-M | 4 |
| Step 3 | Button Signals (×2) | 2 | M-M | 6 |
| Step 4 | LEDs (jumper-less) | 0 | — | 6 |
| Step 5 | Buzzer | 0 | — | 6 (Removed) |
| Step 6 | OLED (GND, VCC, SCL, SDA) | 4 | M-M | 10 ✅ |

> **PIVOT:** To unblock the OLED and solve the M-F cable shortage, the Right Button and Active Buzzer were removed to free up space and 4 M-M cables. The OLED is now mounted directly to the board.

---

## [2026-05-20] Step 1: ESP32 Brain Insertion
**Status:** ✅ Completed

* Inserted the ESP32-WROOM-32 (38-pin variant) into the 400-point breadboard.
* Pushed down firmly until headers are nearly flush.
* **Location:** Rows 1 to 19.

## [2026-05-20] Step 2: Power Rails Wiring
**Status:** ✅ Completed

* `3V3` (j19) -> Right Red (+) rail — 1 M-M wire
* `GND` (j6) -> Right Blue (-) rail — 1 M-M wire

## [2026-05-20] Step 3: The Two Tactile Buttons (Shifted Up)
**Status:** ✅ Completed (Pivot: 3rd button removed)

* **Button Placement:**
  * **Left:** Rows 21 and 23 (`e/f` columns)
  * **Center:** Rows 24 and 26 (`e/f` columns)
* **Grounds:** `j21`, `j24` -> Right Blue (-) rail (2 M-M wires)
* **Signals:**
  * `i23` -> `j7` (GPIO 12) — Left button
  * `i26` -> `j5` (GPIO 13) — Center button

## [2026-05-20] Step 4: LEDs (Visual Outputs) — Jumper-Less
**Status:** ✅ Completed

* **Red LED:** Long leg -> `j11` (GPIO 25), Short leg -> Blue (-) rail row 11
* **Blue LED:** Long leg -> `j10` (GPIO 26), Short leg -> Blue (-) rail row 10

## [2026-05-20] Step 5: Active Buzzer — REMOVED
**Status:** ❌ Removed during pivot

* Buzzer was removed to free up 2 M-M cables and physical space for the OLED display.

## [2026-05-20] Step 6: OLED Display (I2C)
**Status:** ✅ Completed (Pivot)

* **Direct Breadboard Mount:** Plugged directly into `a27-a30`.
* **Wiring (using 4 freed M-M cables):**
  * `GND` (a27) -> Right Blue (-) rail
  * `VCC` (a28) -> Right Red (+) rail
  * `SCL` (a29) -> `j12` (GPIO 33)
  * `SDA` (a30) -> `j13` (GPIO 32)

---

## [2026-05-20] Step 7: PlatformIO CLI Installation
**Status:** ✅ Completed

* `pio` was not on system PATH. Installed via `pip install platformio` into conda base environment.
* **Version installed:** PlatformIO Core 6.1.19

## [2026-05-20] Step 8: Phase 1 Firmware Flash & Verification
**Status:** ✅ PASSED

* Flashed via `pio run --target upload --upload-port COM3`
* ESP32 identified: `ESP32-D0WD (revision v1.0)`, MAC `ec:62:60:11:80:18`
* Serial monitor confirmed boot message at 115200 baud.
* **Test Results (all passed ✅):**
  * Left button → Serial: `Button 1 (Left) Pressed!` + Red LED ON
  * Right button → Serial: `Button 3 (Right) Pressed!` + Blue LED ON
  * Center button → Serial: `Button 2 (Center) Pressed!` + Both LEDs blink rapidly
  * Button release → LEDs off, no serial output

---

## Phase 2 Checklist (Next Session)

* [x] **Step 5:** Pivot - Remove Active Buzzer and Button 3
* [x] **Step 6:** Mount OLED on rows 27-30 and wire with M-M cables
* [ ] **Step 9:** Write Phase 2 firmware test (OLED initialization & text output)
* [ ] **Step 10:** Flash and verify Phase 2
