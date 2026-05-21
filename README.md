# Course 036714: Week 3 - Embedded Game

Welcome to the **Block Breaker** Embedded Systems Game Project! This repository contains the source code, hardware configuration, and design documentation for an ESP32-based arcade game, created as part of the "AI-Assisted Development" course.

## Overview
This project is a fully playable clone of classic games like Breakout and Arkanoid, built natively in C++ for the ESP32 platform. 

### Features
- **Hardware-Accelerated Display:** Uses a 0.96" OLED Display (SSD1306) communicating over a 400kHz I2C bus for high framerates.
- **Delta-Time Physics:** A fully non-blocking game loop driven by `millis()` ensures smooth, sub-pixel physics rendering regardless of CPU load.
- **Dynamic Feedback:** A Blue LED flashes on block impacts, and a Red LED illuminates upon losing a life.
- **Customizable Parameters:** All game tuning settings (paddle speed, ball speed, block layouts) are cleanly separated into `src/game_params.h`.

## Hardware Requirements
- 1x ESP32 Development Board
- 1x 0.96" OLED Display (I2C SSD1306)
- 2x Tactile Buttons
- 2x LEDs (1 Red, 1 Blue)

## Documentation
Detailed documentation on hardware setup, connections, and the game's core specifications can be found in the `docs/` folder:
- [Hardware Setup Guide](docs/Blair_Hardware_Setup_Guide.md)
- [Game Specifications](docs/game_specifications.md)
- [AI Project Blueprint](docs/ai_project_blueprint.md)
- [Expert Insights & Integration Logs](docs/expert_insights_log.md)

## Development Setup
This project is configured to use **PlatformIO** in Visual Studio Code.
- Libraries required (automatically managed via `platformio.ini`):
  - `Adafruit SSD1306`
  - `Adafruit GFX Library`

To compile and upload the game to your board, simply run:
```bash
pio run -t upload
```

## Progress
**Project Complete!** The game has progressed from hardware testing to a fully polished software architecture with all core mechanics, state machines, and visual feedback successfully implemented.
