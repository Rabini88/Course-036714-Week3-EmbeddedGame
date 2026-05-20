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
| Step 3 | Button Grounds (×3) | 3 | M-M | 5 |
| Step 3 | Button Signals (×3) | 3 | M-M | 8 |
| Step 4 | LEDs (jumper-less) | 0 | — | 8 |
| Step 5 | Buzzer Ground + Signal | 2 | M-M | 10 ✅ |
| Step 6 | OLED (GND, VCC, SCL, SDA) | 4 | M-F | ❌ BLOCKED (only 2 M-F available) |

> **BLOCKER:** OLED requires 4 M-F cables. Only 2 are available. Options: (A) Acquire 2 more M-F cables, or (B) solder short leads on the OLED breakout to convert to M-M compatible.

---

## [2026-05-20] Step 1: ESP32 Brain Insertion
**Status:** ✅ Completed

* Inserted the ESP32-WROOM-32 (38-pin variant) into the 400-point breadboard.
* Pushed down firmly until headers are nearly flush.
* **Location:** Rows 1 to 19.

## [2026-05-20] Step 2: Power Rails Wiring
**Status:** ⏸️ Reset (Not Connected)

* Previously connected, then unplugged during reset.
* **To Do:**
  * `3V3` (j19) -> Right Red (+) rail — 1 M-M wire
  * `GND` (j6) -> Right Blue (-) rail — 1 M-M wire

## [2026-05-20] Step 3: The Three Tactile Buttons
**Status:** 🟡 Partially Complete — Physically Placed, Not Wired

* Buttons are physically seated in the breadboard.
* **No cables are connected yet.**
* **Button Placement (can be adjusted if needed):**
  * **Left:** Rows 22 and 24 (`e/f` columns)
  * **Center:** Rows 25 and 27 (`e/f` columns)
  * **Right:** Rows 28 and 30 (`e/f` columns)
* **Wiring To Do:**
  * **Grounds:** `j22`, `j25`, `j28` -> Right Blue (-) rail (3 M-M wires)
  * **Signals:** 
    * `i24` -> `j7` (GPIO 12) — 1 M-M wire
    * `i27` -> `j5` (GPIO 13) — 1 M-M wire
    * `i30` -> `j8` (GPIO 14) — 1 M-M wire

## [2026-05-20] Step 4: LEDs (Visual Outputs) — Jumper-Less
**Status:** ⏸️ Reset (Unplugged)

* Previously inserted, then removed during reset.
* **Plan:** Insert LEDs directly between the ESP32 column j and the Blue (-) rail. No M-M wires needed.
  * **Red LED:** Long leg -> `j11` (GPIO 25), Short leg -> Blue (-) rail row 11
  * **Blue LED:** Long leg -> `j10` (GPIO 26), Short leg -> Blue (-) rail row 10

## [2026-05-20] Step 5: Active Buzzer — Remote Placement
**Status:** ⏸️ Not Started

* **Plan:** Place buzzer in bottom-left corner using final 2 M-M wires.
  * Long leg (+) -> `a27`
  * Short leg (-) -> `a29`
  * **Ground:** `b29` -> Right Blue (-) rail — 1 M-M wire
  * **Signal:** `b27` -> `j9` (GPIO 27) — 1 M-M wire

## [2026-05-20] Step 6: OLED Display (I2C)
**Status:** ❌ Blocked — Insufficient M-F Cables

* Requires 4 M-F cables (GND, VCC, SCL, SDA).
* Only 2 M-F cables available.
* **Resolution Required** before proceeding with Phase 2 assembly.
