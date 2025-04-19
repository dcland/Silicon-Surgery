char password[8]; // Vulnerable buffer

// Function to simulate privilege escalation
void secureFunction() {
  Serial.println("You have bypassed the login system!");
}

// New function to blink an LED
void blinkLed() {
  pinMode(13, OUTPUT); // Built-in LED pin on most Arduino boards
  for (int i = 0; i < 10; i++) {
    digitalWrite(13, HIGH); // Turn the LED on
    delay(500);             // Wait for 500ms
    digitalWrite(13, LOW);  // Turn the LED off
    delay(500);             // Wait for 500ms
  }
  Serial.println("Blinking LED executed!");
}

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino Stack Overflow Demo");
  Serial.println("Enter the password to log in:");
}

void printCharArrayWithExtraBytes(char* charArray) {
    // Print the original char array
    Serial.print("Char Array: ");
    for (size_t i = 0; i < 64; i++) {
        Serial.print(charArray[i]);
    } 
  }

void loop() {
  char input[32]; // Temporary input buffer for demonstration

  // Check for input from the serial console
  if (Serial.available() > 0) {
    // Vulnerable: Read input without bounds checking
    Serial.readBytesUntil('\n', input, 64); // Deliberately too large for stack buffer
    // Function pointer stored on the stack
    void (*funcPtr)() = secureFunction;
    // Overwrite password buffer
    strcpy(password, input); // Unsafe copying without bounds checking

    // Call the function pointer (potentially overwritten)
    funcPtr();
    
    // Reset password buffer for demonstration
    memset(password, 0, sizeof(password));
  }
}
