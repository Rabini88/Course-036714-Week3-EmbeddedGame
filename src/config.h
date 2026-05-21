#ifndef CONFIG_H
#define CONFIG_H

// --- HARDWARE PIN MAPPINGS ---
// Defined according to the physical breadboard layout (ESP32 Right Side/Column j)

// 1. Tactile Buttons (Inputs)
// Wired to ground. Require INPUT_PULLUP in code.
#define PIN_BUTTON_1_LEFT   12
#define PIN_BUTTON_2_CENTER 13
// 2. LEDs (Outputs)
#define PIN_LED_RED         25 // Game Over / Miss
#define PIN_LED_BLUE        26 // Hit / Score

// 4. OLED Display (I2C)
#define PIN_OLED_SDA        32
#define PIN_OLED_SCL        33

#endif // CONFIG_H
