# **Flashing a Binary File Directly to Your Arduino**

If you need to flash a precompiled `.hex` binary instead of an `.ino` sketch, follow these steps:

## **🔹 Extract the Compiled Binary**
1. In Arduino IDE, go to **Sketch > Export Compiled Binary**.
2. Find the `.hex` file in the project directory.

## **🔹 Flashing via avrdude**
1. Open a terminal and run:
   ```bash
   avrdude -p atmega328p -c arduino -P /dev/ttyUSB0 -b 115200 -U flash:w:yourfile.hex:i
   ```
   Replace `/dev/ttyUSB0` with your actual device port.

✅ Your Arduino is now running the flashed binary!
