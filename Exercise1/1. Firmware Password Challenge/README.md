# Exercise 1: Firmware Password Challenge (Arduino)

## Overview

This simple Arduino sketch is designed to simulate a basic "firmware-level" password check. It serves as an introductory exercise for beginners interested in hardware and firmware exploitation.

The goal is to reverse engineer the correct password or brute-force it through the serial interface.

## How It Works

- The Arduino listens for input over the Serial monitor (baud rate: 9600).
- If the input matches the hardcoded password (`s3cr3t`), it turns on the built-in LED and prints **"Access granted"**.
- If the input is incorrect, it prints **"Wrong password"**.

## Hardware Required

- Any basic Arduino board (e.g., Uno, Nano)
- USB cable
- No external components needed

## Upload Instructions

1. Open this sketch in the Arduino IDE.
2. Connect your Arduino board.
3. Select the correct board and port under **Tools**.
4. Upload the sketch.
5. Open the Serial Monitor (`Ctrl+Shift+M`) and set the baud rate to **9600**.

## Challenge for Learners

- Try to find the correct password by interacting with the device (e.g., using brute-force scripts).
- Modify the sketch to make the password dynamic or obfuscated in EEPROM.
- Expand it into a mini CTF-style firmware lock.

## Code Summary

```cpp
#include <Arduino.h>

void setup() {
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
    if (Serial.available()) {
        String input = Serial.readStringUntil('\\n');
        input.trim();
        if (input == "s3cr3t") {
            digitalWrite(LED_BUILTIN, HIGH);
            Serial.println("Access granted");
        } else {
            Serial.println("Wrong password");
        }
    }
}
