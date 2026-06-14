#ifndef CONFIG_H
#define CONFIG_H

// --- HARDWARE PIN MAPPINGS ---
// Defined according to the new flipped physical breadboard layout (ESP32 Left Side)

// 1. Tactile Buttons (Inputs)
// Wired to ground. Require INPUT_PULLUP in code.
#define PIN_BUTTON_LEFT     18
#define PIN_BUTTON_RIGHT    17

// 2. LEDs (Outputs) - Not physically wired, kept for code structure
#define PIN_LED_RED         25 // Game Over / Miss
#define PIN_LED_BLUE        26 // Hit / Score

// 3. Buzzer (Output)
#define PIN_BUZZER          19

// 4. OLED Display (I2C)
#define PIN_OLED_SDA        21
#define PIN_OLED_SCL        22

#endif // CONFIG_H
