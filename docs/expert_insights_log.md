# Expert Insights & Architectural Decisions Log
*A living document capturing key design principles, architectural rules, and resource optimizations established during the project lifecycle.*

## The Manager
* **[2026-05-21] Phase 3 Initiation:** Hardware validation is complete. The Game Specifications (`game_specifications.md`) have been drafted by the team and approved. Development moves into Phase 3 (Software Architecture & Game Logic).
* *Insights and rules related to agile methodology, process management, and project flow.*

## Charlie (Software Architect)
* **[2026-05-21] Non-Blocking Game Architecture:** `delay()` is strictly banned in the game loop. All logic (physics, LED flashes, state transitions) must use `millis()` delta-time checks. Entity positions (ball X/Y) must use `float` to allow for smooth sub-pixel trajectories, preventing rigid 45-degree locks.
* **[2026-05-20] Hardware Abstraction:** We must not hardcode pin numbers into our game logic. Since hardware constraints force us to use specific pins (like 32 and 33 for the OLED), our first software step will be to create a central `config.h` file. We will define all these pins there (e.g., `#define PIN_OLED_SDA 32`). This keeps our codebase modular, so if the hardware changes again, we only update one single file.

## Val (Resource Optimizer)
* **[2026-05-21] I2C Clock Speed for OLED:** The standard 100kHz I2C clock is too slow for 60FPS gaming on a 128x64 display. We must explicitly set `Wire.setClock(400000);` after initialization to quadruple the bandwidth and ensure smooth gameplay.
* **[2026-05-20] Incremental Testing:** Before writing any complex game logic, we must write a minimal test script. This script should only turn on the LEDs, beep the buzzer, and print to the Serial monitor when a button is pressed. Do not proceed to game development until that simple test passes on the exact pin configuration.

## Blair (Embedded Engineer)
* **[2026-05-20] Cable Inventory First — Always.** Before designing any wiring plan, audit your exact cable inventory by type: M-M, M-F, and F-F are NOT interchangeable. The OLED requires M-F cables (to connect to its male header pins), and our initial design assumed 4 M-F cables when we only had 2. This created a hard blocker. In all future sessions, the first question Blair asks is: "What cables do you physically have?"

* **[2026-05-20] Document Actual Placement, Not Planned Placement.** We planned buttons in rows 21-23 but the PI placed them in rows 22-24 due to physical constraints. All downstream wiring coordinates (signal pin rows, ground rows) shifted accordingly. The integration log and setup guide must always reflect what is *actually on the board*, not what was originally designed. If it's not updated, the next debugging session will be chasing ghost connections.

* **[2026-05-20] Jumper-Less Component Insertion.** When an ESP32's GPIO pins in column `j` sit directly adjacent to the power rail, components like LEDs and the buzzer can be inserted directly — long leg into the GPIO hole, short leg bent over into the Blue (-) rail. This technique saves 2 M-M wires per component. Only works for components whose leg span matches the column-j-to-rail gap (~5mm). Always check physical clearance with neighboring components first — the buzzer was too bulky for this and required remote placement.

* **[2026-05-20] Closest Hole = Cleanest Build.** When connecting a pin to a power rail, use the hole on the rail that is directly horizontal from the source pin. Short, straight wires prevent spaghetti, keep components accessible, and reduce accidental disconnects during testing. Stay clear of the ESP32's WiFi antenna area at the top of the board.

* **[2026-05-20] `INPUT_PULLUP` Eliminates Physical Resistors.** Wiring tactile buttons directly from a GPIO pin to GND, combined with `pinMode(PIN, INPUT_PULLUP)` in firmware, activates the ESP32's internal pull-up resistor. This makes the pin read HIGH when unpressed and LOW when pressed. This eliminates the need for any external resistor — critical when working with a minimal component kit.

* **[2026-05-20] Never Assemble Everything Before Testing Anything.** We initially wired LEDs, then the buzzer, before verifying the buttons. This is a compounding risk: a bug anywhere in the system becomes nearly impossible to isolate. The correct embedded workflow is: *add one component, write a minimal test, verify it works, then add the next.* This is now our standing protocol (Phase 1 = Buttons + LEDs, Phase 2 = Buzzer + OLED).

* **[2026-05-20] Component Spacing & Row Isolation.** Tactile buttons span the center trench and connect horizontally. If another component (like a buzzer) shares that same horizontal row, their signals will electrically interfere (e.g., pulling a buzzer pin LOW triggers a phantom button press). Always map out button rows and intentionally leave empty rows between them for placing other components safely.

* **[2026-05-20] Ground Rail Bridging for Bulky Components.** When a component (like the active buzzer) is too wide for standard jumper placement on one side, you can place it across the board so its negative leg plugs directly into the far-side ground rail. Then, bridge the left and right ground rails with a single M-M jumper. This solves grounding without running wires across the busy active columns.

* **[2026-05-20] Windows + Non-ASCII Project Paths = Two Blockers.** When the project lives in a path with Hebrew (or any non-ASCII) characters, PlatformIO on Windows hits two separate failures: (1) `UnicodeEncodeError` when printing warnings — fix with `$env:PYTHONUTF8=1`. (2) `WinError 3` (path not found) from the compiler hitting the 260-char MAX_PATH limit — fix by redirecting `build_dir`, `libdeps_dir`, and `build_cache_dir` in the `[platformio]` section of `platformio.ini` to a short ASCII path (e.g., `C:/pio_ws/`). Both fixes must be applied together.

* **[2026-05-20] CP210x Driver Is Not Pre-Installed on Windows.** The ESP32-WROOM-32 uses a CP2102 USB-to-UART bridge. Windows does not ship with this driver. Without it, the device appears in Device Manager with an Error status and no COM port is assigned. Download the Silicon Labs CP210x driver from silabs.com, install as Administrator, then replug the USB cable. Verify with `Get-PnpDevice | Where-Object {$_.FriendlyName -match 'CP210'}` — Status must show `OK` before flashing.

## Alex (Game Designer)
* **[2026-05-21] 2-Button Block Breaker Mechanics:** Since we pivoted to 2 buttons instead of 3, the game must operate with zero auxiliary controls. Left button moves left, Right button moves right. The ball must auto-serve from the paddle after a 2-second delay on game start or life lost to give the player time to prepare.
* **[2026-05-21] Offloading Feedback to LEDs:** With the buzzer gone, all non-visual feedback shifts to the LEDs. Blue LED should blink on every block break to make hits feel impactful. Red LED should turn solid when the ball drops out of bounds (Game Over/Life Lost) to draw immediate attention away from the screen.
* **[2026-05-21] Paddle Constraints:** The paddle shouldn't be too small on a 128x64 display. Given the SSD1306 resolution, a paddle width of 16-20 pixels is a good starting point, and ball movement needs to use sub-pixel or fractional logic (using floats) to prevent the ball from looking jittery or getting stuck in a pure 45-degree bounce loop.
