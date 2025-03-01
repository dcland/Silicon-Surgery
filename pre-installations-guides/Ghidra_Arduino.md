# **Installing Ghidra & Adding Support for Arduino MCUs**

Ghidra is a powerful open-source reverse engineering tool. This guide will help you install Ghidra and configure it for analyzing Arduino firmware.

## **🔹 Step 1: Download & Install Ghidra**
1. Go to the official [Ghidra website](https://ghidra-sre.org/).
2. Download the latest `.zip` package.
3. Extract the archive and run `ghidraRun`.

## **🔹 Step 2: Add Support for AVR Architecture (Arduino MCUs)**
1. Download the **AVR processor module** from [AVR-Ghidra Plugin](https://github.com/avr-llvm/ghidra-avr).
2. Extract the plugin to `Ghidra/Processors/`.
3. Restart Ghidra and select **AVR** when analyzing Arduino firmware.

✅ Now Ghidra can disassemble Arduino `.hex` files for reverse engineering.
