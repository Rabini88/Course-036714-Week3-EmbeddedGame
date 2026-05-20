#include <Arduino.h>
#include "config.h"

void setup() {
  // Initialize Serial Monitor for debugging
  Serial.begin(115200);
  delay(1000); // Give serial monitor time to open
  Serial.println("--- Phase 1 Hardware Test: Buttons & LEDs ---");

  // Initialize LEDs as OUTPUT
  pinMode(PIN_LED_RED, OUTPUT);
  pinMode(PIN_LED_BLUE, OUTPUT);
  
  // Turn off LEDs initially (assume HIGH is ON for standard wiring)
  digitalWrite(PIN_LED_RED, LOW);
  digitalWrite(PIN_LED_BLUE, LOW);

  // Initialize Buttons as INPUT_PULLUP
  // This means the pin will read HIGH when unpressed, and LOW when pressed (connected to ground).
  pinMode(PIN_BUTTON_1_LEFT, INPUT_PULLUP);
  pinMode(PIN_BUTTON_2_CENTER, INPUT_PULLUP);
  pinMode(PIN_BUTTON_3_RIGHT, INPUT_PULLUP);

  Serial.println("Initialization complete. Waiting for button presses...");
}

void loop() {
  // Read button states (LOW means pressed because of INPUT_PULLUP)
  bool leftPressed   = (digitalRead(PIN_BUTTON_1_LEFT) == LOW);
  bool centerPressed = (digitalRead(PIN_BUTTON_2_CENTER) == LOW);
  bool rightPressed  = (digitalRead(PIN_BUTTON_3_RIGHT) == LOW);

  // 1. Serial Output Test
  if (leftPressed) {
    Serial.println("Button 1 (Left) Pressed!");
  }
  if (centerPressed) {
    Serial.println("Button 2 (Center) Pressed!");
  }
  if (rightPressed) {
    Serial.println("Button 3 (Right) Pressed!");
  }

  // 2. LED Tactile Feedback Test
  // Turn on Red LED if Left button is pressed
  if (leftPressed) {
    digitalWrite(PIN_LED_RED, HIGH);
  } else {
    digitalWrite(PIN_LED_RED, LOW);
  }

  // Turn on Blue LED if Right button is pressed
  if (rightPressed) {
    digitalWrite(PIN_LED_BLUE, HIGH);
  } else {
    digitalWrite(PIN_LED_BLUE, LOW);
  }

  // If center button is pressed, blink both rapidly
  if (centerPressed) {
    digitalWrite(PIN_LED_RED, HIGH);
    digitalWrite(PIN_LED_BLUE, HIGH);
    delay(50);
    digitalWrite(PIN_LED_RED, LOW);
    digitalWrite(PIN_LED_BLUE, LOW);
    delay(50);
  } else {
    // Add a small delay to prevent serial spamming and debounce
    delay(100);
  }
}
