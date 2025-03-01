import serial
import time
import binascii
import argparse
import sys

# Error code mapping
ERROR_CODES = {
    "0": "Enter the password to log in:",
    "1": "Access Granted! Welcome!",
    "2": "Access Denied. Try again.",
    "3": "Error: Address must start with '0x'",
    "4": "Error: Invalid address format",
    "5": "Reading firmware from flash memory...",
    "6": "Firmware read complete.",
    "7": "Unknown command.",
    "8": "Available commands:"
}

# Initialize serial connection
def init_serial(port, baudrate=9600, timeout=1):
    try:
        return serial.Serial(port, baudrate, timeout=timeout)
    except serial.SerialException as e:
        print(f"Error: Could not open serial port {port}: {e}")
        sys.exit(1)

# Function to send a command and read the response
def send_command(ser, command):
    ser.write((command + "\n").encode())
    time.sleep(0.1)
    response = ser.read_all().decode()
    handle_response(response)

# Function to handle responses
def handle_response(response):
    lines = response.splitlines()
    for line in lines:
        if line.isdigit() and line in ERROR_CODES:
            print(f"Arduino Response: {ERROR_CODES[line]}")
        else:
            print(f"Arduino Output: {line}")

# Overflow example
def send_overflow(ser):
    overflow_data = "A" * 128  # Example buffer overflow payload
    send_command(ser, overflow_data)

# Dump flash to a binary file
def dump_flash(ser, output_file="flash_dump.bin"):
    send_command(ser, "dumpflash")
    time.sleep(5)  # Adjust based on expected data size
    data = ser.read_all()
    with open(output_file, "wb") as f:
        f.write(data)
    print(f"Flash dump saved to {output_file}")

# Main function
def main():
    # Parse command-line arguments
    parser = argparse.ArgumentParser(description="Interact with Arduino over serial.")
    parser.add_argument(
        "-p", "--port", required=True, help="Serial port to connect to the Arduino."
    )
    args = parser.parse_args()

    # Initialize the serial connection
    ser = init_serial(port=args.port)

    # Login to the Arduino
    send_command(ser, "secret")  # Replace with the correct password if necessary

    # Send commands and interact with the Arduino
    send_command(ser, "?")  # List available commands
    send_command(ser, "writebyte:0x24 0x20")  # Example: Write a byte
    send_command(ser, "readbyte:0x24")  # Example: Read a byte
    
    # Send an overflow example
    send_overflow(ser)
    
    # Dump flash memory to a file
    dump_flash(ser, "flash_dump.bin")

    # Close the serial connection
    ser.close()

if __name__ == "__main__":
    main()
