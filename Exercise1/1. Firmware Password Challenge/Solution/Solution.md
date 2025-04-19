# 🔐 Bonus Challenges

## 🧪 Bonus 1: Brute Force the Password

To simulate a brute-force password attack on the Arduino over serial, use the provided Python script:

### Requirements
- Python 3
- `pyserial` installed (`pip install pyserial`)

### Usage

```bash
python brute_force_arduino.py
```

Make sure to update the `PORT` in the script to match your Arduino's serial port.

## 🧬 Bonus 2: Extracting the Password from the Firmware Binary

After compiling the sketch, the `.hex` file will contain all the program data, including string literals. You can try to extract the password using:

```bash
strings path/to/firmware.hex | grep -i secret
```

### How to Get the Firmware Binary
1. Open Arduino IDE.
2. Click **Sketch > Export Compiled Binary**.
3. Locate the `.hex` file in your sketch folder.

Alternatively, use the command line:

```bash
arduino-cli compile --fqbn arduino:avr:uno --export-binaries .
```

## 🧠 Bonus 3: Finding the Address of the Password in Flash

Once you have the binary:

```bash
avr-objdump -D -m avr -b ihex firmware.hex > dump.txt
```

Then, search for the string `s3cr3t` in the dump file:

```bash
grep -A 10 s3cr3t dump.txt
```

This shows you the flash memory address where the string is stored.

If you dumped firmware from a live device, this same technique can help find hardcoded secrets.

---

These extras give learners a taste of binary analysis and reverse engineering in a very approachable way.


## 🧰 Bonus 4: Extracting the Password from the ELF File

When compiling an Arduino sketch, the `.elf` file contains all program symbols and strings. You can extract the hardcoded password using tools like `strings`, `nm`, and `objdump`.

### How to Generate the ELF File

If you're using the Arduino CLI:

```bash
arduino-cli compile --fqbn arduino:avr:uno --build-path ./build
```

This will generate `./build/sketch.elf`.

### Extracting Strings from the ELF File

```bash
strings ./build/sketch.elf | grep -i s3cr3t
```

Or list all symbols and find relevant ones:

```bash
avr-nm ./build/sketch.elf | grep s3cr3t
```

### Finding the Address in ELF

```bash
avr-objdump -D ./build/sketch.elf | grep -A 5 s3cr3t
```

This will give you the exact flash address where the password string is stored.

You can also load the ELF into a disassembler like Ghidra or Binary Ninja for further reverse engineering.
