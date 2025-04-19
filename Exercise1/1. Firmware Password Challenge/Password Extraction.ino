
#include <Arduino.h>

void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    if (Serial.available()) {
        input = Serial.readStringUntil('\n');
        input.trim();
        if (input == "s3cr3t") {
          digitalWrite(LED_BUILTIN, HIGH);
          Serial.println("Access granted");
        } else {
          Serial.println("Wrong password");
        }
      }
}
