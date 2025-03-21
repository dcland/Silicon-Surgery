#include <avr/pgmspace.h>

#define FLASH_CHUNK_SIZE 64

// Enum for messages
enum Message {
  MSG_ENTER_PASSWORD = 0,
  MSG_ACCESS_GRANTED,
  MSG_ACCESS_DENIED,
  MSG_INVALID_ADDRESS,
  MSG_INVALID_FORMAT,
  MSG_FIRMWARE_READ,
  MSG_FIRMWARE_COMPLETE,
  MSG_UNKNOWN_COMMAND,
  MSG_AVAILABLE_COMMANDS
};

char inputBuffer[64] = {0};
char password[8];  // Vulnerable buffer
bool isAuthenticated = false;

// // Function to convert enum to string
// const char*(Message msg){
//   switch (msg) {
//     case MSG_ENTER_PASSWORD: return "Enter the password to log in:";
//     case MSG_ACCESS_GRANTED: return "Access Granted! Welcome!";
//     case MSG_ACCESS_DENIED: return "Access Denied. Try again.";
//     case MSG_INVALID_ADDRESS: return "Error: Address must start with '0x'";
//     case MSG_INVALID_FORMAT: return "Error: Invalid address format";
//     case MSG_FIRMWARE_READ: return "Reading firmware from flash memory...";
//     case MSG_FIRMWARE_COMPLETE: return "Firmware read complete.";
//     case MSG_UNKNOWN_COMMAND: return "Unknown command.";
//     case MSG_AVAILABLE_COMMANDS: return "Available commands:";
//     default: return "Unknown message.";
//   }
// }

void setup() {
  Serial.begin(9600);
  Serial.println(MSG_ENTER_PASSWORD);
  while (!login());
}

void debug() {
  Serial.print("isAuthenticated: ");
  Serial.println(isAuthenticated);
}

// Function to convert a hex string to an unsigned long
unsigned long parseHexAddress(const char* hexString) {
    if (strncmp(hexString, "0x", 2) != 0) {
        Serial.println(MSG_INVALID_ADDRESS);
        return 0;
    }
    char* endPtr;
    unsigned long address = strtoul(hexString, &endPtr, 16);
    if (*endPtr != '\0') {
        Serial.println(MSG_INVALID_FORMAT); 
        return 0;
    }
    return address;
}

void writeByte(unsigned long address, byte value) {
    byte* ptr = (byte*)address;  
    *ptr = value;
    Serial.print("Address 0x");
    Serial.print(address, HEX);
    Serial.print(": 0x ");
    Serial.println(value, HEX);                
}

byte readByte(unsigned long address) {
    Serial.print("Address 0x");
    Serial.print(address, HEX);
    byte* ptr = (byte*)address;
    return *ptr;                 
}

bool login() {
  if (isAuthenticated) {
    return true;
  }
  if (Serial.available() > 0) {
    Serial.readBytesUntil('\n', password,  );  // Vulnerable: No bounds checking
    password[sizeof(password) - 1] = '\0';      // Ensure null termination

    if (strcmp(password, "secret") == 0) {
      isAuthenticated = true;
    }
    
    memset(password, 0, sizeof(password));
    
    if (isAuthenticated) {
      Serial.println(MSG_ACCESS_GRANTED);
      return true;
    } else {
      Serial.println(MSG_ACCESS_DENIED);
      return false;
    }
  }
}

void dumpFLASH() {
  //Serial.println(MSG_FIRMWARE_READ);
  for (unsigned long address = 0; address < 0x8000; address += FLASH_CHUNK_SIZE) {
    for (int i = 0; i < FLASH_CHUNK_SIZE; i++) {
      byte data = pgm_read_byte(address + i);  
      Serial.write(data);  
    }
    delay(50);
  }
  Serial.println(MSG_FIRMWARE_COMPLETE);
}

void loop() {
    if (Serial.available() > 0 && isAuthenticated) {
      Serial.readBytesUntil('\n', inputBuffer, sizeof(inputBuffer) - 1);
      inputBuffer[sizeof(inputBuffer) - 1] = '\0';

      if (strncmp(inputBuffer, "dumpflash", 9) == 0) {
          dumpFLASH();
      } 
      else if (strncmp(inputBuffer, "readbyte:", 9) == 0) {
        unsigned long start;
        if (sscanf(inputBuffer + 9, "%lx", &start) == 1) {
          byte res = readByte(start);
          Serial.print("addr 0x");
          Serial.print(start, HEX);
          Serial.print(": 0x");
          Serial.println(res, HEX);
        } else {
          Serial.println(MSG_INVALID_ADDRESS);
        }
      } 
      else if (strncmp(inputBuffer, "writebyte:", 10) == 0) {
        unsigned long addr;
        byte value;
        if (sscanf(inputBuffer + 10, "%lx %hhx", &addr, &value) == 2){
          writeByte(addr, value);
        }
      }
      else if (strncmp(inputBuffer, "debug", 5) == 0) {
          debug();
      }  
      else if (strncmp(inputBuffer, "?", 1) == 0) {
        Serial.println(MSG_AVAILABLE_COMMANDS);
        Serial.println(" - dumpflash");
        Serial.println(" - readbyte:ADDR");
        Serial.println(" - writebyte:ADDR VALUE");
        Serial.println(" - debug");
      }
      else {
        Serial.println(MSG_UNKNOWN_COMMAND);
      }
      memset(inputBuffer, 0, sizeof(inputBuffer));
    }
}
