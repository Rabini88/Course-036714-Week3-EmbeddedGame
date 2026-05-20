# Expert Insights & Architectural Decisions Log
*A living document capturing key design principles, architectural rules, and resource optimizations established during the project lifecycle.*

## The Manager
* *Insights and rules related to agile methodology, process management, and project flow.*

## Charlie (Software Architect)
* **[2026-05-20] Hardware Abstraction:** We must not hardcode pin numbers into our game logic. Since hardware constraints force us to use specific pins (like 32 and 33 for the OLED), our first software step will be to create a central `config.h` file. We will define all these pins there (e.g., `#define PIN_OLED_SDA 32`). This keeps our codebase modular, so if the hardware changes again, we only update one single file.

## Val (Resource Optimizer)
* **[2026-05-20] Incremental Testing:** Before writing any complex game logic, we must write a minimal test script. This script should only turn on the LEDs, beep the buzzer, and print to the Serial monitor when a button is pressed. Do not proceed to game development until that simple test passes on the exact pin configuration.

## Blair (Embedded Engineer)
* *Insights related to physical hardware, wiring, power management, and microcontroller specific constraints.*

## Alex (Game Designer)
* *Insights related to game mechanics, user experience, timing, feedback loops, and player interaction.*
