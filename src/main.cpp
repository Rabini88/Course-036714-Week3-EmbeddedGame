#include <Arduino.h>
#include "config.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// -1 means no reset pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("--- Phase 2.1 Hardware Test: Buttons, LEDs & OLED ---");

  // Initialize LEDs
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);
  digitalWrite(PIN_LED_RED, LOW);
  digitalWrite(PIN_LED_BLUE, LOW);

  // Initialize Buttons
  pinMode(PIN_BUTTON_1_LEFT, INPUT_PULLUP);
  pinMode(PIN_BUTTON_2_CENTER, INPUT_PULLUP);

  // Initialize I2C with the custom pins
  Wire.begin(PIN_OLED_SDA, PIN_OLED_SCL);

  // Initialize OLED
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed. Check I2C wiring."));
    for(;;); // Don't proceed, loop forever
  }

  // Flip the screen 180 degrees to match breadboard mounting
  display.setRotation(2);

  // Clear the buffer
  display.clearDisplay();

  // Draw some text
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("OLED Initialized!"));
  display.println(F("Waiting for inputs..."));
  display.display();
  
  Serial.println("Initialization complete. Waiting for button presses...");
}

void loop() {
  bool leftPressed   = (digitalRead(PIN_BUTTON_1_LEFT) == LOW);
  bool centerPressed = (digitalRead(PIN_BUTTON_2_CENTER) == LOW);

  // Default display state
  display.clearDisplay();
  display.setCursor(0,0);
  display.println(F("Press a button:"));
  display.setCursor(0, 16);

  // --- Left Button: Red LED ---
  if (leftPressed) {
    Serial.println("Button 1 (Left) Pressed!");
    digitalWrite(PIN_LED_RED, HIGH);
    display.setTextSize(2);
    display.println(F("LEFT"));
  } else {
    digitalWrite(PIN_LED_RED, LOW);
  }

  // --- Center Button: Blue LED ---
  // (We use blue for center now that 3rd button is gone, or we can blink both)
  if (centerPressed) {
    Serial.println("Button 2 (Center) Pressed!");
    digitalWrite(PIN_LED_RED, HIGH);
    digitalWrite(PIN_LED_BLUE, HIGH);
    display.setTextSize(2);
    display.println(F("CENTER"));
    delay(50);
    digitalWrite(PIN_LED_RED, LOW);
    digitalWrite(PIN_LED_BLUE, LOW);
    delay(50);
  } else {
    if (!leftPressed) {
      digitalWrite(PIN_LED_BLUE, LOW);
      display.setTextSize(1);
      display.println(F("[Idle]"));
    }
  }

  display.display();
  delay(100);
}


