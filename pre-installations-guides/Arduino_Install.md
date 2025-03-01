# **Installing Arduino IDE on Windows, Linux, and Mac**

The Arduino IDE is the official development environment for programming Arduino boards. Follow the steps below to install it on your operating system.

## **🔹 Windows Installation**
1. Go to the official [Arduino download page](https://www.arduino.cc/en/software).
2. Download the **Windows Installer (.exe)** version.
3. Run the installer and follow the on-screen instructions.
4. Allow the driver installation when prompted.
5. Once installed, launch Arduino IDE and connect your Arduino via USB.

## **🔹 Linux Installation**
1. Open a terminal and run:
   ```bash
   sudo apt update
   sudo apt install arduino
   ```
   Alternatively, you can download the latest `.tar.xz` from the [official website](https://www.arduino.cc/en/software) and extract it manually.
2. Add your user to the **dialout** group to access serial ports:
   ```bash
   sudo usermod -aG dialout $USER
   ```
3. Restart your computer and launch Arduino IDE.

## **🔹 macOS Installation**
1. Download the macOS `.zip` package from the [official Arduino page](https://www.arduino.cc/en/software).
2. Open the `.zip` file and drag **Arduino.app** into the Applications folder.
3. If you get a security warning, go to **System Preferences > Security & Privacy > Allow Arduino**.
4. Open Arduino IDE and connect your Arduino board.

✅ Now your Arduino IDE is ready to use!
