import serial
import time

PORT = '/dev/ttyUSB0'  # Change this to your Arduino's port (e.g., COM3 on Windows)
BAUD = 9600

# Wordlist (could be expanded)
wordlist = ['1234', 'admin', 'test', 'password', 's3cr3t', 'letmein', 'arduino']

def main():
    ser = serial.Serial(PORT, BAUD, timeout=1)
    time.sleep(2)  # Allow Arduino to reset
    for pwd in wordlist:
        print(f"Trying: {pwd}")
        ser.write((pwd + '\n').encode())
        time.sleep(0.5)
        response = ser.read(100).decode(errors='ignore')
        print(response.strip())
        if "Access granted" in response:
            print(f"Found password: {pwd}")
            break

if __name__ == "__main__":
    main()
